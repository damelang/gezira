Color <: [a, r, g, b : Real]
Point <: [x, y : Real]
Matrix <: [a, b, c, d, e, f : Real]
Bezier <: [a, b, c : Point]
EdgeContribution <: [x, y, w, h : Real]

Sampler :: Point >> Color
Compositor :: [Color, Color] >> Color
Canvas :: (start : Point) : [Color, Real] >>|

(m : Matrix × p : Point) : Point
    [m.a × p.x + m.c × p.y + m.e,
     m.b × p.x + m.d × p.y + m.f]

(‖ a : Point ‖) : Real
    √(a.x × a.x + a.y × a.y) 

CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
    ⇒ Interleave (s1, s2) → c

UniformColor (c : Color) : Sampler
    ∀ p
        >> [c.a, c.a × c.r, c.a × c.g, c.a × c.b]

CompositeOver : Compositor
    ∀ [a, b]
        >> a + b × (1 - a.a)

FillBetweenEdges (x0 : Real) : EdgeContribution >> Real
    x = x0
    local = 0
    run   = 0
    ∀ [x', y, w, h]
        n = x' - x
        run' = run + h
        if n = 0
            local' = local + w × h
        else
            local' = run + w × h
            >>        | local | ⋖ 1
            >(n - 1)> | run   | ⋖ 1
    if local ≠ 0
        >> | local | ⋖ 1

CreateSamplePoints (start : Point) : Real >> Point
    x = start.x
    y = start.y
    ∀ c
        x' = x + 1
        >> [x, y]

Render' (s : Sampler, c : Canvas) : EdgeContribution >>|
    & [x, y, w, h]
        p = [x, y] + 0.5
        ⇒ FillBetweenEdges (x) →
          Interleave (CreateSamplePoints (p) → s, (→)) →
          c (p)

Render (s : Sampler, c : Canvas) : EdgeContribution >>|
    ⇒ GroupBy (@y) → SortBy (@x) → Render' (s, c)
