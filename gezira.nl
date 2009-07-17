Point <: [x, y : Real]
Bezier <: [A, B, C : Point]
Color <: [a, r, g, b : ColorComponent]
EdgeContribution <: [x, y, w, h : Real]
Matrix <: [a, b, c, d, e, f : Real]
Texturer <: (x, y : Real, i : Image) : ColorComponent >> Color
Blender <: [Color, Color] >> Color

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
        else if ∨[ bmax ≤ min ∨ max ≤ bmin ]
            A' ← min ⋗ A ⋖ max
            C' ← min ⋗ C ⋖ max
            >> [A', A' ~~ C', C']
        else 
            ABBC    ← (A ~~ B) ~~ (B ~~ C)
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← ABBC ?nearmin? min ?nearmax? max
            << [A, A ~~ B, M] << [M, B ~~ C, C]

DecomposeBezier : Bezier >> EdgeContribution
    ∀ [A, B, C]
        if ∧[ ⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉ ]
            P ← ⌊ A ⌋ ⋖ ⌊ C ⌋
            w ← P.x + 1 - (C.x ~~ A.x)
            h ← C.y - A.y
            >> [P.x, P.y, w, h]
        else
            ABBC    ← (A ~~ B) ~~ (B ~~ C)
            min     ← ⌊ ABBC ⌋
            max     ← ⌈ ABBC ⌉
            nearmin ← | ABBC - min | < 0.1
            nearmax ← | ABBC - max | < 0.1
            M       ← ABBC ?nearmin? min ?nearmax? max
            << [A, A ~~ B, M] << [M, B ~~ C, C]

FillBetweenEdges (x : Real) : EdgeContribution >> ColorComponent
    local ← 0 : Real
    run   ← 0 : Real
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

UniformColor (c : Color) : Texturer
    ∀ _
        >> c

BlendOver : Blender
    ∀ [A, B]
        >> A + B ∙ (1 - A.a)

BlendTextures (t1 : Texturer, t2 : Texturer, b : Blender) : Texturer
    -> Interleave (t1 (x, y, i), t2 (x, y, i)) -> b

PixelPipeline (t : Texturer, i : Image) : EdgeContribution >> _
    & [x, y, _, _]
        sx <- x + 0.5
        sy <- y + 0.5
        -> FillBetweenEdges (x) -> Interleave (t (sx, sy, i), Echo) ->
           WriteImage (sx, sy, i)

Renderer (t : Texturer, i : Image) : Bezier >> _
    -> DecomposeBezier -> GroupBy (@y) -> SortBy (@x) -> PixelPipeline (t, i)
