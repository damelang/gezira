OffsetBezier (o : Real, Bi : Bezier) : Bezier >> Bezier
    A = Bi.A
    B = Bi.B
    C = Bi.C
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
        ⇒ OffsetBezier (o, (M, B ~ C, C)) → OffsetBezier (o, (A, A ~ B, M))

JoinOffsets (o : Real, P : Point, u, v : Vector) : Bezier >> Bezier
        A = P + o × u
        C = P + o × v
        w = ^(u.y - v.y, v.x - u.x) ?? u
        if u ∙ w < -0.01
            >> (A, A ~ C, C)
        else if u ∙ w < 0.9
            ⇒ JoinOffsets (o, P, u, w) → JoinOffsets (o, P, w, v)
        else
            N = P + o × w
            B = 2 × N - (A ~ C)
            >> (A, B, C)

OffsetAndJoinBezierPath (o : Real, B0, Bi : Bezier) : Bezier >> Bezier
    bic = Bi.C
    u = Bi.B ⟂ Bi.C
    ∀ Bj
        v = Bj.A ⟂ Bj.B
        ⇒ OffsetAndJoinBezierPath (o, B0, Bj) → JoinOffsets (o, bic, u, v) → OffsetBezier (o, Bi)
    vv = { B0.A ⟂ B0.B if Bi.C #= B0.A,
           Bi.C ⟂ Bi.B                  }
    ⇒ JoinOffsets (o, bic, u, vv) → OffsetBezier (o, Bi)

StrokeOneSide (o : Real) : Bezier >> Bezier
    ∀ B0
        ⇒ OffsetAndJoinBezierPath (o, B0, B0) → (→)

ReverseBeziers : Bezier >> Bezier
    ∀ (A, B, C)
        >> (C, B, A)
        
StrokeBezierPath (o : Real) : Bezier >> Bezier
    ⇒ DupCat (StrokeOneSide (o),
              Reverse → ReverseBeziers → StrokeOneSide (o)) → (→)
