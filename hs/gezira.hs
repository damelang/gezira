{-# LANGUAGE FlexibleInstances #-}

import Prelude(Ord(..), Num(..), Fractional(..), Float, Monad(..), Eq(..), Show(..),
               (&&), (||), sqrt, putStrLn, map, zipWith, repeat)

a ⋖ b = min a b
a ⋗ b = max a b
a ≤ b = a <= b
a ∧ b = a && b
a ∨ b = a || b
a ~~ b = (a + b) / 2

infixl 7 ~~
infixl 4 ≤, ⋖, ⋗
infixl 3 ∧, ∨

data Vector a = Vector [a] deriving (Eq, Show)

vfoldl1 :: (a -> a -> a) -> Vector a -> a
vfoldl1 f (Vector l) = foldl1 f l

unless :: (Vector a) -> ((Vector Bool), (Vector a)) -> (Vector a)
unless (Vector a) t = map choose (zip a t)
  where choose a (q, b) = if q then b else a

-- pairwise application over Vector
instance Num a => Num (Vector a) where
    Vector a + Vector b = Vector (zipWith (+) a b)
    Vector a - Vector b = Vector (zipWith (-) a b)
    Vector a * Vector b = Vector (zipWith (*) a b)
    abs (Vector a)      = Vector (map abs a)
    signum (Vector a)   = Vector (map signum a)
    fromInteger a       = Vector (repeat (fromInteger a))

class (Num a) => NileNum a where
    (∙) :: (Num b, Num c) => a -> b -> c

type Real = Float
type ColorComponent = Float

-- Point :: [x, y : Real]
type Point = Vector Real

-- Bezier :: [A, B, C : Point]
type Bezier = Vector Point

-- Pixel :: [a, r, g, b : ColorComponent]
type Pixel = Vector ColorComponent

-- Image :: [[Pixel]]
type Image = [[Pixel]]

-- CoverageAlpha :: ColorComponent
type CoverageAlpha = ColorComponent

-- PixelComposition :: [A, B : Pixel]
type PixelComposition = Vector Pixel

-- Texturer :: CoverageAlpha >> Pixel
type Texturer = Real -> Real -> [CoverageAlpha] -> [Pixel]

-- Compositor :: PixelComposition >> Pixel
type Compositor = [PixelComposition] -> [Pixel]

-- EdgeContribution :: [x, y, width, height : Real]
type EdgeContribution = Vector Real

-- Matrix :: [a, b, c, d, e, f : Real]
type Matrix = Vector Real

{-
(M : Matrix ∙ P : Point) : Point
    [M.a ∙ P.x + M.c ∙ P.y + M.e,
     M.b ∙ P.x + M.d ∙ P.y + M.f]
-}
{-
instance NileNum Matrix where
  Matrix (a:b:c:d:e:f:_) ∙ Point (x:y:_) = Point [a * x + c * y + e, b * x + d * y + f]
 -}

{-
TransformBezier (M : Matrix) : Bezier >> Bezier
    ∀ [A, B, C]
        [M ∙ A, M ∙ B, M ∙ C]
-}
transformBezier :: Matrix -> [Bezier] -> [Bezier]
transformBezier m input =
    do (a, b, c) <- input
       [(m ∙ a, m ∙ b, m ∙ c)]

{-
ClipBezier (min, max : Point) : Bezier >> Bezier
    ∀ [A, B, C]
        bmin ← A ⋖ B ⋖ C
        bmax ← A ⋗ B ⋗ C
        if ∧[min ≤ bmin ∧ bmax ≤ max]
            [A, B, C] >>
        elseif ∨[bmax ≤ min ∨ max ≤ bmin]
            A' ← min ⋗ A ⋖ max
            C' ← min ⋗ C ⋖ max
            [A', A' ~~ C', C'] >>
        else 
            AB      ← A ~~ B
            BC      ← B ~~ C
            ABBC    ← AB ~~ BC
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← nearmin ? min : nearmax ? max : ABBC
            [A, AB, M] >> [M, BC, C] >> self
-}
clipBezier :: Point -> Point -> [Bezier] -> [Bezier]
clipBezier max min input =
     do (a, b, c) <- input
        let bmin = a ⋖ b ⋖ c
            bmax = a ⋗ b ⋗ c
        if vfoldl1 (∧) (min ≤ bmin ∧ bmax ≤ max)
          then [(a, b, c)]
          else if vfoldl1 (∨) (bmax ≤ min ∨ max ≤ bmin)
               then let a' = min ⋗ a ⋖ max
                        c' = min ⋗ c ⋖ max
                    in [(a', a' ~~ c', c')]
               else
                   let ab   = a ~~ b
                       bc   = b ~~ c
                       abbc = ab ~~ bc
                       nearmin = abs (abbc - min) < Vector [0.1, 0.1]
                       nearmax = abs (abbc - max) < Vector [0.1, 0.1]
                       m = abbc `unless` (nearmin, min) `unless` (nearmax, max)
                   in clipBezier max min [(a, ab, m), (m, bc, c)]

{-
DecomposeBezier : Bezier >> EdgeContribution
    ∀ [A, B, C]
        if ∧[ ⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉ ]
            P      ← ⌊ A ⌋ ⋖ ⌊ C ⌋
            width  ← P.x + 1 - (C.x ~~ A.x)
            height ← C.y - A.y
            [P.x, P.y, width, height] >>
        else
            AB      ← A ~~ B
            BC      ← B ~~ C
            ABBC    ← AB ~~ BC
            min     ← ⌊ ABBC ⌋
            max     ← ⌈ ABBC ⌉
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← ABBC ?nearmin? min ?nearmax? max
            [A, AB, M] >> [M, BC, C] >> self
-}
decomposeBezier :: [Bezier] -> [EdgeContribution]
decomposeBezier input =
    do (a, b, c) <- input
      if vfoldl1 (∧) ((floor a == floor c) ∨ (ceiling a == ceiling c))
      then let p      = (floor a) ⋖ (floor c)
               width  = p!!0 + 1 - (c!!0 ~~ a!!0)
               height = c!!1 - a!!1
           in  [(p!!0, p!!1, width, height)]
      else let AB   = A ~~ B
               BC   = B ~~ C
               ABBC = AB ~~ BC
               min  = floor ABBC
               max  = ceiling ABBC
               nearmin = abs (abbc - min) < Vector [0.1, 0.1]
               nearmax = abs (abbc - max) < Vector [0.1, 0.1]
               m = abbc `unless` (nearmin, min) `unless` (nearmax, max)
           in  decomposeBezier [(a, ab, m), (m, bc, c)]

{-
FillBetweenEdges (x' : Real) : EdgeContribution >> CoverageAlpha
    local ← 0
    run   ← 0
    ∀ [x, y, width, height]
        n ← x - x'
        if n = 0
            local ← local + width ∙ height
            run   ← run   + height
        else
            >>        | local | ⋖ 1
            >(n - 1)> | run   | ⋖ 1 
            x'    ← x
            local ← run + width ∙ height
            run   ← run + height
    >> | local | ⋖ 1
-}
fillBetweenEdges :: Real -> [EdgeContribution] -> [CoverageAlpha]
fillBetweenEdges = fillBetweenEdges' 0 0
              
fillBetweenEdges' :: Real -> Real -> Real -> [EdgeContribution] -> [CoverageAlpha]
fillBetweenEdges' local run x' [] = (abs local) ⋖ 1
fillBetweenEdges' local run x' [EdgeContribution (x:y:width:height:xs)] =
    if n == 0
        fillBetweenEdges' (local + width ∙ height) (run + height) x' xs
    else
        let local' = (abs local) ⋖ 1
            run'   = (abs run)   ⋖ 1
        [local'] ++
        (replicate (n - 1) run') ++
        fillBetweenEdges' (run + width ∙ height) (run + height) x xs
    where n = x - x'

{-
SolidColor (x, y : Real, color : Pixel) : Texturer
    ∀ coverage
        >> color ∙ coverage
-}
solidColor :: Pixel -> Real -> Real -> [CoverageAlpha] -> [Pixel]
solidColor color y x input =
    do coverage <- input
       [(color ∙ [coverage, coverage, coverage, coverage])]

{-
CompositeOver : Compositor
    ∀ [A, B]
        >> A + B ∙ (1 - A.a)
-}
compositeOver :: [PixelComposition] -> [Pixel]
compositeOver input
    do (a, b) <- input
       [(a + b ∙ [1 - a.a, 1 - a.a, 1 - a.a, 1 - a.a])]

{-
PixelPipeline (target     : Image,
               texturer   : Texturer,
               compositor : Compositor) : EdgeContribution >> _
    peek [x, y, _, _]
        self >> FillBetweenEdges (x) >>
                Interleave (texturer (x, y), ReadArray (target[y], x)) >>
                compositor >> WriteArray (target[y], x)
-}
pixelPipeline :: Compositor -> Texturer -> Image -> [EdgeContribution] -> Bool
pixelPipeline compositor texturer target =

main = putStrLn "done"
