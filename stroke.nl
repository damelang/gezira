StrokeJoin :: (o : Real) : (Bezier, Bezier) >> Bezier

StrokeOffset (o : Real) : Bezier >> Bezier
    ∀ (A, B, C)
        u = A ⟂ B
        v = B ⟂ C
        M = (A ~ B) ~ (B ~ C)
        if u ∙ v > 0.9
            w = (A ~ B) ⟂ (B ~ C)
            D = A + o × u
            F = C + o × v
            N = M + o × w
            E = 2 × N - (D ~ F)
            >> (D, E, F)
        else if ¬(u &= 0) ∧ ¬(v &= 0)
            << (A, A ~ B, M) << (M, B ~ C, C)

StrokeJoinMiter (l, d : Real) : StrokeJoin
    ∀ ((A, B, C), (D, E, F))
        u = B ⟂ C
        v = D ⟂ E
        x = B ⇀ C
        y = E ⇀ D
        w = ^(x + y) ?? u
        G = C + o × u
        J = C + o × v
        if u ∙ w < 0
            >> (G, G ~ J, J)
        else if u ∙ w < l
            p = d × (x ∙ w)
            H = G + p × x
            I = J + p × y
            >> (G, G ~ H, H) >> (H, H ~ I, I) >> (I, I ~ J, J)
        else
            q = o / (u ∙ w)
            N = C + q × w
            >> (G, G ~ N, N) >> (N, N ~ J, J)

StrokeJoinRound : StrokeJoin
    ∀ ((A, B, C), (D, E, F))
        u = B ⟂ C
        v = D ⟂ E
        x = B ⇀ C
        y = E ⇀ D
        w = ^(x + y) ?? u
        G = C + o × u
        J = C + o × v
        if u ∙ w < 0
            >> (G, G ~ J, J)
        else if u ∙ w < 0.9
            z = (w.y, -w.x)
            << ((A, B, C), (C, C + z, C + z))
            << ((C - z, C - z, C), (D, E, F))
        else
            N = C + o × w
            H = 2 × N - (G ~ J)
            >> (G, H, J)

PrepareBeziersForStroke : Bezier >> Bezier
    ∀ (A, B, C)
        u = A ⟂ B
        v = B ⟂ C
        if u ∙ v < -0.9999
            L = (A - B) / ((A - 2 × B + C) ? 1)
            t = L.x ? L.y
            M = (1 - t) × (1 - t) × A + 2 × (1 - t) × t × B + t × t × C
            >> (A, A ~ M, M) >> (M, M ~ C, C)
        else if u &= 0 ∨ v &= 0
            M = A ~ C
            if ¬(A ⟂ M &= 0) ∧ ¬(M ⟂ C &= 0)
                >> (A, M, C)
        else
            >> (A, B, C)

PrepareBeziersForOffset : Bezier >> Bezier
    ∀ (A, B, C)
        >> (A, B, C) >> (C, B, A)

PrepareBeziersForJoin : Bezier >> (Bezier, Bezier)
    & (A, B, C)
    first = 1
    D = 0
    E = 0
    F = 0
    ∀ (D', E', F')
        if first
            first' = 0
        else
            >> ((D, E, F), (D', E', F')) >> ((F', E', D'), (F, E, D))
    if A = F ∧ first = 0
        >> ((D, E, F), (A, B, C)) >> ((C, B, A), (F, E, D))

PrepareBeziersForCap : Bezier >> (Bezier, Bezier)
    & (A, B, C)
    D = 0
    E = 0
    F = 0
    ∀ (D', E', F')
    if A ≠ F
        >> ((C, B, A), (A, B, C)) >> ((D, E, F), (F, E, D))

StrokeBeziers (o : Real, j, c : StrokeJoin) : Bezier >> Bezier
    ⇒ PrepareBeziersForStroke → Mix (PrepareBeziersForOffset → StrokeOffset (o), Mix (PrepareBeziersForJoin → j (o), PrepareBeziersForCap → c (o)))
