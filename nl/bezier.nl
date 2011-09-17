TransformBeziers (M : Matrix) : Bezier >> Bezier
    ∀ (A, B, C)
        >> (M ⊗ A, M ⊗ B, M ⊗ C)

ClipBeziers (min, max : Point) : Bezier >> Bezier
    ∀ (A, B, C)
        bmin    = A ◁ B ◁ C
        bmax    = A ▷ B ▷ C
        inside  = min  ≤ bmin ∧ bmax ≤ max
        outside = bmax ≤ min  ∨ max  ≤ bmin
        if inside.x ∧ inside.y
            >> (A, B, C)
        else if outside.x ∨ outside.y
            cA = min ▷ A ◁ max
            cC = min ▷ C ◁ max
            >> (cA, cA ~ cC, cC)
        else
            ABBC    = (A ~ B) ~ (B ~ C)
            nearmin = | ABBC - min | < 0.1
            nearmax = | ABBC - max | < 0.1
            M       = {min if nearmin, max if nearmax, ABBC}
            << (M, B ~ C, C) << (A, A ~ B, M) 

CalculateBounds : Bezier >> (Point, Point)
    min =  999999 : Point
    max = -999999 : Point
    ∀ (A, B, C)
        if ¬(A.y = B.y ∧ B.y = C.y)
            min' = min ◁ A ◁ B ◁ C
            max' = max ▷ A ▷ B ▷ C
    >> (min, max)
