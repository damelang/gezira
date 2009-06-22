Point <: [x, y : Real]
Bezier <: [A, B, C : Point]
Pixel <: [a, r, g, b : ColorComponent]
CoverageAlpha <: ColorComponent
Texturer <: (x, y : Real) : CoverageAlpha >> Pixel
Compositor <: [Pixel, Pixel] >> Pixel
EdgeContribution <: [x, y, w, h : Real]
Matrix <: [a, b, c, d, e, f : Real]

(M : Matrix ∙ P : Point) : Point
    [M.a ∙ P.x + M.c ∙ P.y + M.e,
     M.b ∙ P.x + M.d ∙ P.y + M.f]

TransformBezier (M : Matrix) : Bezier >> Bezier
    ∀ [A, B, C]
        >> [M ∙ A, M ∙ B, M ∙ C]

ClipBezier (min, max : Point) : Bezier >> Bezier
    ∀ [A, B, C]
        bmin ← A ⋖ B ⋖ C
        bmax ← A ⋗ B ⋗ C
        if ∧[ min ≤ bmin ∧ bmax ≤ max ]
            >> [A, B, C]
        elseif ∨[ bmax ≤ min ∨ max ≤ bmin ]
            A' ← min ⋗ A ⋖ max
            C' ← min ⋗ C ⋖ max
            >> [A', A' ~~ C', C']
        else 
            AB      ← A ~~ B
            BC      ← B ~~ C
            ABBC    ← AB ~~ BC
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← ABBC ?nearmin? min ?nearmax? max
            << [A, AB, M] << [M, BC, C]

DecomposeBezier : Bezier >> EdgeContribution
    ∀ [A, B, C]
        if ∧[ ⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉ ]
            P ← ⌊ A ⌋ ⋖ ⌊ C ⌋
            w ← P.x + 1 - (C.x ~~ A.x)
            h ← C.y - A.y
            >> [P.x, P.y, w, h]
        else
            AB      ← A ~~ B
            BC      ← B ~~ C
            ABBC    ← AB ~~ BC
            min     ← ⌊ ABBC ⌋
            max     ← ⌈ ABBC ⌉
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← ABBC ?nearmin? min ?nearmax? max
            << [A, AB, M] << [M, BC, C]

FillBetweenEdges (x : Real) : EdgeContribution >> CoverageAlpha
    local ← 0
    run   ← 0 
    ∀ [x', y, w, h]
        n ← x' - x
        if n = 0
            local ← local + w ∙ h
            run   ← run   + h
        else
            >>        | local | ⋖ 1
            >(n - 1)> | run   | ⋖ 1
            x     ← x'
            local ← run + w ∙ h
            run   ← run + h
    if local ≠ 0
        >> | local | ⋖ 1

UniformColor (color : Pixel) : Texturer
    ∀ coverage
        >> color ∙ coverage

CompositeOver : Compositor
    ∀ [A, B]
        >> A + B ∙ (1 - A.a)

PixelPipeline (target     : Image,
               texturer   : Texturer,
               compositor : Compositor) : EdgeContribution >> ⏚
    & [x, y, _, _]
        -> FillBetweenEdges (x) >>
           Interleave2 (texturer (x + 0.5, y + 0.5), ReadImage (target, x, y)) >>
           compositor >> WriteImage (target, x, y)

Renderer (target     : Image, width    : Real,
          height     : Real,  texturer : Texturer,
          compositor : Compositor) : Bezier >> ⏚
    -> ClipBezier ([0, 0], [width, height]) >>
       DecomposeBezier >> GroupBy (@y) >> SortBy (@x) >>
       PixelPipeline (target, texturer, compositor)
