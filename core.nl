Point <: [x, y]
Color <: [a, r, g, b]
Bezier <: [a, b, c : Point]
Matrix <: [a, b, c, d, e, f]
EdgeContribution <: [p : Point, w, h]

Sampler :: (start : Point) : Real >> Color
Canvas :: (start : Point) : [Color, Real] >>|
Compositor :: [Color, Color] >> Color

CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
    ➔ Interleave (s1 (start), s2 (start)) ➔ c

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
            >>        | local | ⋖ 1
            >(n - 1)> | run   | ⋖ 1
            local' = run + w × h
            run'   = run + h
    if local ≠ 0
        >> | local | ⋖ 1

Render (s : Sampler, c : Canvas) : EdgeContribution >>|
    ➔ GroupBy (@p.y) ➔ SortBy (@p.x) ➔
        & [p, _, _]
            ➔ FillBetweenEdges (p) ➔ Interleave (s (p + 0.5), Id) ➔ c (p + 0.5)
