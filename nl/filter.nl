BilinearFilterPoints : Point >> Point
    ∀ P
        S = ⌊ P - 0.5 ⌋ + 0.5
        x = S.x
        y = S.y
        >> (x, y    ) >> (x + 1, y    )
        >> (x, y + 1) >> (x + 1, y + 1)

BilinearFilterWeights : Point >> Real
    ∀ P 
        S = P - ⌊ P - 0.5 ⌋ - 0.5
        u = S.x
        v = S.y
        >> (1 - u) × (1 - v) >> u × (1 - v)
        >> (1 - u) × (    v) >> u × (    v)

{-
BilinearFilterEnd : (Color, Real) >> Color
    ∀ (c1, w1), (c2, w2), (c3, w3), (c4, w4)
        >> c1 × w1 + c2 × w2 + c3 × w3 + c4 × w4
-}

BilinearFilterCombine : (Color, Real) >> Color
    n   = 1
    sum = 0 : Color
    ∀ (c, w)
        if n = 4
            >> sum + c × w
            n'   = 1
            sum' = 0
        else
            n'   = n + 1
            sum' = sum + c × w

BilinearFilter (s : Sampler) : Sampler
    ⇒ Interleave (BilinearFilterPoints → s,
                  BilinearFilterWeights    ) → BilinearFilterCombine
