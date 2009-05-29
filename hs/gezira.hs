import Prelude(Ord(..), Num(..), Fractional(..), Float, Monad(..),
               (&&), (||), sqrt, putStrLn)

instance (Num a, Num b) => Num (a, b) where
    (ax, ay) + (bx, by) = (ax + bx, ay + by)
    (ax, ay) - (bx, by) = (ax - bx, ay - by)
    (ax, ay) * (bx, by) = (ax * bx, ay * by)
    abs (x, y)          = (abs x, abs y)
    signum (x, y)       = (signum x, signum y)
    fromInteger x       = (fromInteger x, fromInteger x)

a ⋖ b = min a b
a ⋗ b = max a b

-- logical functions for Point
(ax, ay) ≤ (bx, by) = (ax <= bx, ay <= by)
(ax, ay) ∧ (bx, by) = (ax && bx, ay && by)
(ax, ay) ∨ (bx, by) = (ax || bx, ay || by)
and_ (x, y) = x && y -- unary ∧
or_ (x, y) = x || y -- unary ∨

(~~) :: Point -> Point -> Point
(ax, ay) ~~ (bx, by) = ((ax + bx) / 2, (ay + by) / 2)

infixl 4 ≤, ⋖, ⋗
infixl 3 ∧, ∨

type Real = Float
type ColorComponent = Float

-- Point :: [x, y : Real]
type Point = (Real, Real)

-- Bezier :: [A, B, C : Point]
type Bezier = (Point, Point, Point)

-- Pixel :: [a, r, g, b : ColorComponent]
type Pixel = (ColorComponent, ColorComponent, ColorComponent, ColorComponent)

-- Image :: [[Pixel]]
type Image = [[Pixel]]

-- CoverageAlpha :: ColorComponent
type CoverageAlpha = ColorComponent

-- PixelComposition :: [A, B : Pixel]
type PixelComposition = (Pixel, Pixel)

-- Texturer :: CoverageAlpha >> Pixel
type Texturer = [CoverageAlpha] -> [Pixel]

-- Compositor :: PixelComposition >> Pixel
type Compositor = [PixelComposition] -> [Pixel]

-- EdgeContribution :: [at, width, height : Point, Real, Real]
type EdgeContribution = (Point, Real, Real)

-- Matrix :: [a, b, c, d, e, f : Real]
type Matrix = (Real, Real, Real, Real, Real, Real)

{-
(M : Matrix ∙ P : Point) : Point
    [M.a ∙ P.x + M.c ∙ P.y + M.e,
     M.b ∙ P.x + M.d ∙ P.y + M.f]
 -}
(∙) :: Matrix -> Point -> Point
(a, b, c, d, e, f) ∙ (x, y) = (a * x + c * y + e, b * x + d * y + f)

{-
TransformBezier (M : Matrix) : Bezier >> Bezier
    ∀ [A, B, C]
        [M ∙ A, M ∙ B, M ∙ C]
-}

transformBezier :: Matrix -> [Bezier] -> [Bezier]
transformBezier m input =
    do (a,b,c) <- input
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
        if and_ (min ≤ bmin ∧ bmax ≤ max)
          then [(a, b, c)]
          else if or_ (bmax ≤ min ∨ max ≤ bmin)
               then let a' = min ⋗ a ⋖ max
                        c' = min ⋗ c ⋖ max
                    in [(a', a' ~~ c', c')]
               else
                   let ab   = a ~~ b
                       bc   = b ~~ c
                       abbc = ab ~~ bc
                       nearmin = abs (abbc - min) < (0.1, 0.1)
                       nearmax = abs (abbc - max) < (0.1, 0.1)
                       m       = if nearmin then min else if nearmax then max else abbc
                   in clipBezier max min [(a, ab, m), (m, bc, c)]

{-
DecomposeBezier : Bezier >> EdgeContribution
    ∀ [A, B, C]
        if ∧[ ⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉ ]
            at     ← ⌊ A ⌋ ⋖ ⌊ C ⌋
            width  ← at.x + 1 - (C.x ~~ A.x)
            height ← C.y - A.y
            [at, width, height] >>
        else
            AB      ← A ~~ B
            BC      ← B ~~ C
            ABBC    ← AB ~~ BC
            min     ← ⌊ ABBC ⌋
            max     ← ⌈ ABBC ⌉
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← nearmin ? min : nearmax ? max : ABBC
            [A, AB, M] >> [M, BC, C] >> self
-}

{-
FillBetweenEdges (x : Real) : EdgeContribution >> CoverageAlpha
    local ← 0
    run   ← 0
    ∀ [at, width, height]
        n ← at.x - x
        if n = 0
            local ← local + width ∙ height
            run   ← run   + height
        else
            | local | ⋖ 1 >>
            | run   | ⋖ 1 >(n - 1)>
            x     ← at.x
            local ← run + width ∙ height
            run   ← run + height
-}

{-
SolidColor (offset : Point, color : Pixel) : Texturer
    ∀ coverage
        color ∙ coverage >>
-}

{-
CompositeOver : Compositor
    ∀ [A, B]
        A + B ∙ (1 - A.a) >>
-}

{-
PixelPipeline (target     : Image,
               texturer   : Texturer,
               compositor : Compositor) : EdgeContribution >> _
    first [at, _, _]
        self >> FillBetweenEdges (at.x) >>
                Interleave (texturer (at), ReadArray (target[at.y], at.x)) >>
                compositor >> WriteArray (target[at.y], at.x)
-}

{-
Renderer (target     : Image,
          texturer   : Texturer,
          compositor : Compositor) : Bezier >> _
    self >> ClipBezier ([0, 0], [‖ target[0] ‖, ‖ target ‖]) >>
            DecomposeBezier >> GroupBy ('at.y) >> SortBy ('at.x) >>
            PixelPipeline (target, texturer, compositor)
-}

main = putStrLn "done"
