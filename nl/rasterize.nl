EdgeSample <: (x, y, a, h : Real)

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

CombineEdgeSamples : EdgeSample >> EdgeSpan
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
                l = {x' - x - 1 if |H| > 0.5, 0}
                >> (x, y, |A| ◁ 1, l)
                A' = H + a
                H' = H + h
        else
            >> (x, y, |A| ◁ 1, 0)
            A' = a
            H' = h
    >> (x, y, |A| ◁ 1, 0)

Rasterize : Bezier >> EdgeSpan
    ⇒ DecomposeBeziers → SortBy (@x) → SortBy (@y) → CombineEdgeSamples

RectangleSpans (min, max : Point) : Real >> EdgeSpan
    l = max.x - min.x - 1
    x = min.x + 0.5
    << min.y + 0.5
    ∀ y
        if y < max.y
            >> (x, y, 1, l)
            << y + 1
