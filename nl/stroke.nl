OffsetBezier (o : Real, Z : Bezier) : Bezier >> Bezier
    A = Z.A
    B = Z.B
    C = Z.C
    u = A ⟂ B
    v = B ⟂ C
    M = (A ~ B) ~ (B ~ C)
    if u ∙ v ≥ 0.9
        w = (A ~ B) ⟂ (B ~ C)
        D = A + o × u
        F = C + o × v
        N = M + o × w
        E = 2 × N - (D ~ F)
        >> (D, E, F)
    else if u ≠* 0 ∧ v ≠* 0
        ⇒ OffsetBezier (o, (M, B ~ C, C)) → OffsetBezier (o, (A, A ~ B, M))

MiterJoin (o, l : Real, P : Point, u, v : Vector) : Bezier >> Bezier
    A = P + o × u
    C = P + o × v
    w = (A ⟂ C) ?* u
    if u ∙ w ≥ (1 / l)
        p = o / (u ∙ w)
        M = P + p × w
        >> (M, M ~ C, C) >> (A, A ~ M, M)
    else
        >> (A, A ~ C, C)

RoundJoin (o : Real, P : Point, u, v : Vector) : Bezier >> Bezier
    A = P + o × u
    C = P + o × v
    w = (A ⟂ C) ?* u
    if u ∙ w ≥ 0.9
        N = P + o × w
        B = 2 × N - (A ~ C)
        >> (A, B, C)
    else
        ⇒ RoundJoin (o, P, w, v) → RoundJoin (o, P, u, w)

JoinBeziers (o, l : Real, Zi, Zj : Bezier) : Bezier >> Bezier
    u = Zi.B ⟂ Zi.C
    v = Zj.A ⟂ Zj.B
    if l < 1
        ⇒ RoundJoin (o, (Zi.C), u, v) → (→)
    else
        ⇒ MiterJoin (o, l, (Zi.C), u, v) → (→)

CapBezier (o, c : Real, Z : Bezier) : Bezier >> Bezier
    C = Z.C
    u = Z.B ⟂ Z.C
    v = (u.y, -u.x)
    if c < 0
        ⇒ RoundJoin (o, C, u, -u) → (→)
    else
        D = C + o × u
        G = C - o × u
        E = D + c × v
        F = G + c × v
        >> (D, D ~ E, E) >> (E, E ~ F, F) >> (F, F ~ G, G)

OffsetAndJoin (o, l, c : Real, Z1, Zi : Bezier) : Bezier >> Bezier
    ∀ Zj
        ⇒ OffsetAndJoin (o, l, c, Z1, Zj) → JoinBeziers (o, l, Zi, Zj) → OffsetBezier (o, Zi)
    if Zi.C.x = Z1.A.x ∧ Zi.C.y = Z1.A.y
        ⇒ JoinBeziers (o, l, Zi, Z1) → OffsetBezier (o, Zi)
    else
        ⇒ CapBezier (o, c, Zi) → OffsetBezier (o, Zi)

StrokeOneSide (w, l, c : Real) : Bezier >> Bezier
    ∀ Z1
        ⇒ OffsetAndJoin ((w / 2), l, c, Z1, Z1) → (→)

ReverseBeziers : Bezier >> Bezier
    ∀ (A, B, C)
        >> (C, B, A)

SanitizeBezierPath : Bezier >> Bezier
    ∀ (A, B, C)
        u = A ⟂ B
        v = B ⟂ C
        M = A ~ C
        if u ∙ v < -0.9999
            << (A, M, C)
        else if u ≠* 0 ∧ v ≠* 0
            >> (A, B, C)
        else if (A ⟂ M) ≠* 0 ∧ (M ⟂ C) ≠* 0
            >> (A, M, C)

StrokeBezierPath (w, l, c : Real) : Bezier >> Bezier
    ⇒ SanitizeBezierPath →
      DupCat (StrokeOneSide (w, l, c),
              Reverse → ReverseBeziers → StrokeOneSide (w, l, c))
