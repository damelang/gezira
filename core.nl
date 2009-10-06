Color <: [a, r, g, b]
Point <: [x, y]
Matrix <: [a, b, c, d, e, f]
Bezier <: [a, b, c : Point]
EdgeContribution <: [p : Point, w, h]

Sampler :: Point >> Color
Compositor :: [Color, Color] >> Color
Canvas :: (start : Point) : [Color, Real] >>|

(m : Matrix × p : Point) : Point
    [m.a × p.x + m.c × p.y + m.e,
     m.b × p.x + m.d × p.y + m.f]

CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
    → Interleave (s1, s2) → c

UniformColor (c : Color) : Sampler
    ∀ _
        >> [c.a, c.a × c.r, c.a × c.g, c.a × c.b]

CompositeOver : Compositor
    ∀ [a, b]
        >> a + b × (1 - a.a)

FillBetweenEdges (start : Point) : EdgeContribution >> Real
    x = start.x
    local = 0
    run   = 0
    ∀ [[x', y], w, h]
        n = x' - x
        if n = 0
            local' = local + w × h
            run'   = run   + h
        else
            local' = run + w × h
            run'   = run + h
            >>        | local | ⋖ 1
            >(n - 1)> | run   | ⋖ 1
    if local ≠ 0
        >> | local | ⋖ 1

CreateSamplePoints (start : Point) : Real >> Point
    x = start.x
    y = start.y
    ∀ _
        x' = x + 1
        >> [x, y]

Render (s : Sampler, c : Canvas) : EdgeContribution >>|
    → GroupBy (@p.y) → SortBy (@p.x) →
        & [p, _, _]
            → FillBetweenEdges (p) →
              Interleave (→ CreateSamplePoints (p + 0.5) → s, Id) →
              c (p + 0.5)
