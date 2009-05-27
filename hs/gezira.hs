-- Point :: [x, y : Real]
type Point = (Real, Real)

-- Bezier :: [A, B, C : Point]
type Bezier = (Point, Point)

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
(*) :: Matrix -> Point -> Point
(a, b, c, d, e, f) * (x, y) = (a * x + c * y + e, b * x + d * y + f)

{-
TransformBezier (M : Matrix) : Bezier >> Bezier
    ∀ [A, B, C]
        [M ∙ A, M ∙ B, M ∙ C]
-}
transformBezier :: Matrix -> [Bezier] -> [Bezier]
transformBezier M input
  do ((A, B, C)) <- input
     [(M * A, M * B, M * C)]

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
  do ((A, B, C)) <- input
     let bmin = (A
     if
       
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
