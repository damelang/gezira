OffsetBezier (Z:Bezier, o:Real) : Bezier >> Bezier
    ϵ = 0.1
    (A, B, C) = Z
    (u, v)    = (A ⟂ B, B ⟂ C)
    M         = (A ~ B) ~ (B ~ C)
    if u ∙ v ≥ 1 - ϵ
        w = (A ~ B) ⟂ (B ~ C)
        D = A + ou
        F = C + ov
        N = M + ow
        E = 2N - (D ~ F)
        >> (D, E, F)
    else if A ≠ B ≠ C
        → OffsetBezier ((M, B ~ C, C), o) → OffsetBezier ((A, A ~ B, M), o)

MiterJoin (P:Point, u:Vector, v:Vector, o:Real, l:Real) : Bezier >> Bezier
    (A, C) = (P + ou, P + ov)
    w      = (A ⟂ C) ? u
    m      = 1 / (l ▷ 1)
    if u ∙ w ≥ m
        p = o / (u ∙ w)
        M = P + pw
        >> (M, M ~ C, C) >> (A, A ~ M, M)
    else
        >> (A, A ~ C, C)

RoundJoin (P:Point, u:Vector, v:Vector, o:Real) : Bezier >> Bezier
    ϵ = 0.1
    (A, C) = (P + ou, P + ov)
    w      = (A ⟂ C) ? u
    if u ∙ w ≥ 1 - ϵ
        N = P + ow
        B = 2N - (A ~ C)
        >> (A, B, C)
    else
        → RoundJoin (P, u, w, o) → RoundJoin (P, w, v, o)

JoinBeziers (Zi:Bezier, Zj:Bezier, o:Real, l:Real) : Bezier >> Bezier
    (u, v) = (Zi.B ⟂ Zi.C, Zj.A ⟂ Zj.B)
    C      = Zi.C
    if l < 0
        → RoundJoin (o, C, u, v)
    else
        → MiterJoin (o, C, u, v, l)

CapBezier (Z:Bezier, o:Real, c:Real) : Bezier >> Bezier
    (A, B, C) = Z
    u         = B ⟂ C
    v:Vector  = (u.y, -u.x)
    if c < 0
        → RoundJoin (o, C, u, -u)
    else
        D = C +  ou
        G = C -  ou
        E = D + cov
        F = G + cov
        >> (D, D ~ E, E) >> (E, E ~ F, F) >> (F, F ~ G, G)

OffsetAndJoin (Zi:Bezier, Z1:Bezier, o:Real, l:Real, c:Real) : Bezier >> Bezier
    ∀ Zj
        → OffsetAndJoin (Zj, Z1, o, l, c) →
          JoinBeziers   (Zi, Zj, o, l)    → OffsetBezier (Zi, o)
    if Zi.C = Z1.A
        → JoinBeziers (Zi, Z1, o, l) → OffsetBezier (Zi, o)
    else
        → CapBezier (Zi, o, c)       → OffsetBezier (Zi, o)

StrokeOneSide (width:Real, limit:Real, cap:Real) : Bezier >> Bezier
    ∀ Z1
        → OffsetAndJoin (Z1, Z1, width / 2, limit, cap)

ReverseBeziers () : Bezier >> Bezier
    ∀ (A, B, C)
        >> (C, B, A)

SanitizeBezierPath () : Bezier >> Bezier
    ∀ (A, B, C)
        (u, v) = (A ⟂ B, B ⟂ C)
        if u ∙ v ≈ -1
            M = (A ~ B) ~ (B ~ C)
            << (M, M ~ C, C) << (A, A ~ M, M)
        else if A ≉ B ≉ C
            >> (A, B, C)
        else if A ~ C ≉ B
            << (A, A ~ C, C)

StrokeBezierPath (width:Real, limit:Real, cap:Real) : Bezier >> Bezier
    → SanitizeBezierPath () →
      DupCat (→ StrokeOneSide (width, limit, cap),
              → Reverse () → ReverseBeziers () → StrokeOneSide (width, limit, cap))
