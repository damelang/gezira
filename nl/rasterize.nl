DecomposeBeziers () : Bezier >> EdgeSample
    ϵ = 0.1
    ∀ (A, B, C)
        P = ⌊A⌋ ◁ ⌊C⌋
        if ∧(P ≤ (A, C) ≤ P + 1)
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
                    M, otherwise     }
            << (N, B ~ C, C) << (A, A ~ B, N) 

CombineEdgeSamples () : EdgeSample >> SpanCoverage
    (x, y, A, H) = (0, 0, 0, 0)
    ∀ (x', y', a, h)
        A' = { a,     if y' ≠ y
               H + a, if x' ≠ x
               A + a, otherwise  }
        H' = { h,     if y' ≠ y
               H + h, otherwise  }
        if x' ≠ x ∨ y' ≠ y
            >> (x, y, |A| ◁ 1, 1)
        if y' = y
            >> (x + 1, y, |H| ◁ 1, x' - x - 1)
    >> (x, y, |A| ◁ 1, 1)

Rasterize () : Bezier >> SpanCoverage
    → DecomposeBeziers () → SortBy (1) → SortBy (2) → CombineEdgeSamples ()

RectangleSpans (x1:Number, y1:Number, x2:Number, y2:Number) : Point >> SpanCoverage
    l = x2 - x1 - 1
    << (x1 + 0.5, y1 + 0.5)
    ∀ (x, y)
        if y < y2
            >> (x, y, 1, l)
            << (x, y + 1)
