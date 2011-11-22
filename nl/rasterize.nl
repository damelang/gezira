DecomposeBeziers : Bezier >> EdgeSample
    ∀ (A, B, C)
        inside = (⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉)
        if inside.x ∧ inside.y
            P = ⌊ A ⌋ ◁ ⌊ C ⌋
            w = P.x + 1 - (C.x ~ A.x)
            h = C.y - A.y
            >> (P.x + 1/2, P.y + 1/2, w × h, h)
        else
            ABBC    = (A ~ B) ~ (B ~ C)
            min     = ⌊ ABBC ⌋
            max     = ⌈ ABBC ⌉
            nearmin = | ABBC - min | < 0.1
            nearmax = | ABBC - max | < 0.1
            M       = {min if nearmin, max if nearmax, ABBC}
            << (M, B ~ C, C) << (A, A ~ B, M) 

CombineEdgeSamples : EdgeSample >> CoverageSpan
    x = 0
    y = 0
    A = 0
    H = 0
    ∀ (x', y', a, h)
        if y' = y
            if x' = x
                A' = A + a
                H' = H + h
            else
                >> (x,     y, |A| ◁ 1,          1)
                >> (x + 1, y, |H| ◁ 1, x' - x - 1)
                A' = H + a
                H' = H + h
        else
            >> (x, y, |A| ◁ 1, 1)
            A' = a
            H' = h
    >> (x, y, |A| ◁ 1, 1)

Rasterize : Bezier >> CoverageSpan
    ⇒ DecomposeBeziers → SortBy (@x) → SortBy (@y) → CombineEdgeSamples

RectangleSpans (min, max : Point) : Point >> CoverageSpan
    l = max.x - min.x
    << min + 0.5
    ∀ (x, y)
        if x < max.x ∧ y < max.y
            >> (x, y, 1, l)
            << (x, y + 1)
