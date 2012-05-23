DecomposeBeziers () : Bezier >> EdgeSample
    ϵ = 0.1
    ∀ Z
        (A, B, C) = Z
        P         = ⌊A⌋ ◁ ⌊C⌋
        if ∧(P ≤ Z ≤ P + 1)
            (x, y) = P
            (w, _) = P + 1 - (A ~ C)
            (_, h) = C - A
            >> (x + 0.5, y + 0.5, wh, h)
        else
            M            = (A ~ B) ~ (B ~ C)
            ( min,  max) = (⌊M⌋, ⌈M⌉)
            (Δmin, Δmax) = (M - min, M - max)
            N = { min, if |Δmin| < ϵ
                  max, if |Δmax| < ϵ
                    M,     otherwise }
            << (N, B ~ C, C) << (A, A ~ B, N) 

CombineEdgeSamples () : EdgeSample >> SpanCoverage
    (x, y, A, H) = (0, 0, 0, 0)
    ∀ (x', y', a, h)
        if y' = y
            if x' = x
                (A', H') = (A + a, H + h)
            else
                (A', H') = (H + a, H + h)
                >> (x,     y, |A| ◁ 1,          1)
                >> (x + 1, y, |H| ◁ 1, x' - x - 1)
        else
            (A', H') = (a, h)
            >> (x, y, |A| ◁ 1, 1)
    >> (x, y, |A| ◁ 1, 1)

Rasterize () : Bezier >> SpanCoverage
    → DecomposeBeziers () → SortBy (1) → SortBy (2) → CombineEdgeSamples ()

RectangleSpans (x1:Real, y1:Real, x2:Real, y2:Real) : Point >> SpanCoverage
    l = x2 - x1
    << (x1 + 0.5, y1 + 0.5)
    ∀ (x, y)
        if y < y2
            >> (x, y, 1, l)
            << (x, y + 1)
