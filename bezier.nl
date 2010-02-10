TransformBeziers (M : Matrix) : Bezier >> Bezier
    ∀ (A, B, C)
        >> (M × A, M × B, M × C)

ClipBeziers (min, max : Point) : Bezier >> Bezier
    ∀ (A, B, C)
        bmin   = A ⋖ B ⋖ C
        bmax   = A ⋗ B ⋗ C
        inside = min  ≤ bmin ∧ bmax ≤ max
        cross  = bmax ≤ min  ∨ max  ≤ bmin
        if inside.x ∧ inside.y
            >> (A, B, C)
        else if cross.x ∨ cross.y
            cA = min ⋗ A ⋖ max
            cC = min ⋗ C ⋖ max
            >> (cA, cA ~ cC, cC)
        else
            ABBC    = (A ~ B) ~ (B ~ C)
            nearmin = | ABBC - min | < 0.1
            nearmax = | ABBC - max | < 0.1
            M       = {min if nearmin, max if nearmax, ABBC}
            << (A, A ~ B, M) << (M, B ~ C, C)

DecomposeBeziers : Bezier >> EdgeContribution
    ∀ (A, B, C)
        inside = ⌊ A ⌋ = ⌊ C ⌋ ∨ ⌈ A ⌉ = ⌈ C ⌉
        if inside.x ∧ inside.y
            P = ⌊ A ⌋ ⋖ ⌊ C ⌋
            w = P.x + 1 - (C.x ~ A.x)
            h = C.y - A.y
            >> (P.x, P.y, w, h)
        else
            ABBC    = (A ~ B) ~ (B ~ C)
            min     = ⌊ ABBC ⌋
            max     = ⌈ ABBC ⌉
            nearmin = | ABBC - min | < 0.1
            nearmax = | ABBC - max | < 0.1
            M       = {min if nearmin, max if nearmax, ABBC}
            << (A, A ~ B, M) << (M, B ~ C, C)
