FillBetweenEdges (x : Real) : EdgeContribution >> ColorComponent
    local : Real = 0
    run   : Real = 0
    ∀ [x', y, w, h]
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

FillAndTexture (t : Texturer, i : Image) : EdgeContribution >>|
    & [x, y, _, _]
        sx = x + 0.5
        sy = y + 0.5
        -> FillBetweenEdges (x) -> Interleave (t (sx, sy, i), Echo) ->
           WriteImage (sx, sy, i)

Render (t : Texturer, i : Image) : Bezier >>|
    -> DecomposeBezier -> GroupBy (@y) -> SortBy (@x) -> FillAndTexture (t, i)
