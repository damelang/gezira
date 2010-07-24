Canvas :: (start : Point) : (Color, Real) >>|

DecomposeBeziers : Bezier >> EdgeContribution
    ∀ (A, B, C)
        inside = (⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉)
        if inside.x ∧ inside.y
            P = ⌊ A ⌋ ◁ ⌊ C ⌋
            w = P.x + 1 - (C.x ~ A.x)
            h = C.y - A.y
            >> (P.x, P.y, w, h)
        else
            ABBC    = (A ~ B) ~ (B ~ C)
            min     = ⌊ ABBC ⌋
            max     = ⌈ ABBC ⌉
            nearmin = | ABBC - min | < 0.1
            nearmax = | ABBC - max | < 0.1
            M       = {min if nearmin, max if nearmax, ABBC}
            << (A, A ~ B, M) << (M, B ~ C, C)

FillBetweenEdges (x0 : Real) : EdgeContribution >> Real
    x     = x0
    local = 0
    run   = 0
    ∀ (x', _, w, h)
        n    = x' - x
        run' = run + h
        if n = 0
            local' = local + w × h
        else
            local' = run + w × h
            >>        | local | ◁ 1
            >(n - 1)> | run   | ◁ 1
    if local ≠ 0
        >> | local | ◁ 1

CreateSamplePoints (start : Point) : Real >> Point
    x = start.x
    y = start.y
    ∀ _
        >> (x, y)
        x' = x + 1

Render' (s : Sampler, c : Canvas) : EdgeContribution >>|
    & (x, y, _, _)
    start = (x, y) + 0.5
    ⇒ FillBetweenEdges (x) →
      Interleave (CreateSamplePoints (start) → s, (→)) →
      c (start)

Render (s : Sampler, c : Canvas) : Bezier >>|
    ⇒ DecomposeBeziers → GroupBy (@y) → SortBy (@x) → Render' (s, c)
