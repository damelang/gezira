FillBetweenEdges (x : Real) : EdgeContribution >> Alpha
    local : Real = 0
    run   : Real = 0
    ∀ [[x', y], w, h]
        n = x' - x
        if n = 0
            local' = local + w ∙ h
            run'   = run   + h
        else
            >>        | local | ⋖ 1
            >(n - 1)> | run   | ⋖ 1
            local' = run + w ∙ h
            run'   = run + h
    if local ≠ 0
        >> | local | ⋖ 1

Render (s : Sampler, c : Canvas) : EdgeContribution >>|
    -> GroupBy (@p.y) -> SortBy (@p.x) ->
        & [p]
            -> FillBetweenEdges (p.x) -> Interleave (s (p + 0.5), Id) -> c (p + 0.5)

CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
    -> Interleave (s1 (start), s2 (start)) -> c

UniformColor (c : Color) : Sampler
    ∀ _
        >> c
