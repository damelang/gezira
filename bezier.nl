(M : Matrix ∙ P : Point) : Point
    [M.a ∙ P.x + M.c ∙ P.y + M.e,
     M.b ∙ P.x + M.d ∙ P.y + M.f]

TransformBezier (M : Matrix) : Bezier >> Bezier
    ∀ [A, B, C]
        >> [M ∙ A, M ∙ B, M ∙ C]

ClipBezier (min, max : Point) : Bezier >> Bezier
    ∀ [A, B, C]
        bmin = A ⋖ B ⋖ C
        bmax = A ⋗ B ⋗ C
        if ∧[ min ≤ bmin ∧ bmax ≤ max ]
            >> [A, B, C]
        else if ∨[ bmax ≤ min ∨ max ≤ bmin ]
            cA = min ⋗ A ⋖ max
            cC = min ⋗ C ⋖ max
            >> [cA, cA ~~ cC, cC]
        else 
            ABBC    = (A ~~ B) ~~ (B ~~ C)
            nearmin = | ABBC - min | < 0.1
            nearmax = | ABBC - max | < 0.1
            M       = ABBC ?nearmin? min ?nearmax? max
            << [A, A ~~ B, M] << [M, B ~~ C, C]

DecomposeBezier : Bezier >> EdgeContribution
    ∀ [A, B, C]
        if ∧[ ⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉ ]
            P = ⌊ A ⌋ ⋖ ⌊ C ⌋
            w = P.x + 1 - (C.x ~~ A.x)
            h = C.y - A.y
            >> [P.x, P.y, w, h]
        else
            ABBC    = (A ~~ B) ~~ (B ~~ C)
            min     = ⌊ ABBC ⌋
            max     = ⌈ ABBC ⌉
            nearmin = | ABBC - min | < 0.1
            nearmax = | ABBC - max | < 0.1
            M       = ABBC ?nearmin? min ?nearmax? max
            << [A, A ~~ B, M] << [M, B ~~ C, C]
