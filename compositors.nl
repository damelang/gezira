(A : Color ⊕ B : Color) : Color
    A ∙ (1 - B.a) + B ∙ (1 - A.a)

CompositeClear : Compositor
    ∀ [A, B]
        >> 0

CompositeSrc : Compositor
    ∀ [A, B]
        >> A

CompositeDst : Compositor
    ∀ [A, B]
        >> B

CompositeOver : Compositor
    ∀ [A, B]
        >> A + B ∙ (1 - A.a)

CompositeDstOver : Compositor
    ∀ [A, B]
        >> B + A ∙ (1 - B.a)

CompositeSrcIn : Compositor
    ∀ [A, B]
        >> A ∙ B.a

CompositeDstIn : Compositor
    ∀ [A, B]
        >> B ∙ A.a

CompositeSrcOut : Compositor
    ∀ [A, B]
        >> A ∙ (1 - B.a)

CompositeDstOut : Compositor
    ∀ [A, B]
        >> B ∙ (1 - A.a)

CompositeSrcAtop : Compositor
    ∀ [A, B]
        >> A ∙ B.a + B ∙ (1 - A.a)

CompositeDstAtop : Compositor
    ∀ [A, B]
        >> B ∙ A.a + A ∙ (1 - B.a)

CompositeXor : Compositor
    ∀ [A, B]
        >> A ⊕ B

CompositePlus : Compositor
    ∀ [A, B]
        >> (A + B) ⋖ 1
        
CompositeMultiply : Compositor
    ∀ [A, B]
        >> A ∙ B + A ⊕ B

CompositeScreen : Compositor
    ∀ [A, B]
        >> A + B - A ∙ B

CompositeOverlay : Compositor
    ∀ [A, B]
        C = A.a ∙ B.a - 2 ∙ (B.a - B) ∙ (A.a - A) + A ⊕ B
        D = 2 ∙ A ∙ B + A ⊕ B
        >> C ?(2 ∙ B < B.a)? D

CompositeDarken : Compositor
    ∀ [A, B]
        >> (A ∙ B.a) ⋖ (B ∙ A.a) + A ⊕ B

CompositeLighten : Compositor
    ∀ [A, B]
        >> (A ∙ B.a) ⋗ (B ∙ A.a) + A ⊕ B

CompositeColorDodge : Compositor
    ∀ [A, B]
        C = (B ∙ A.a / (1 - A / A.a) + A ⊕ B) ⋖ 1
        D = A.a ∙ B.a + A ⊕ B
        >> C ?(A ∙ B.a + B ∙ A.a ≥ A.a ∙ B.a)? D

CompositeColorBurn : Compositor
    ∀ [A, B]
        C = A.a ∙ (A ∙ B.a + B ∙ A.a - A.a ∙ B.a) / A + A ⊕ B
        >> C ?(A ∙ B.a + B ∙ A.a ≤ A.a ∙ B.a)? A ⊕ B

CompositeHardLight : Compositor
    ∀ [A, B]
        C = A.a ∙ B.a - 2 ∙ (B.a - B) ∙ (A.a - A) + A ⊕ B
        D = 2 ∙ A ∙ B + A ⊕ B
        >> C ?(2 ∙ A < A.a)? D

CompositeSoftLight : Compositor
    ∀ [A, B]
        C = (1 - B / B.a) ∙ (2 ∙ A - A.a)
        D = B ∙ (A.a - C) + A ⊕ B
        E = B ∙ (A.a - C ∙ (3 - 8 ∙ B / B.a)) + A ⊕ B
        F = B ∙ A.a + (√(B / B.a) ∙ B.a - B) ∙ (2 ∙ A - A.a) + A ⊕ B
        >>  (F ?(B ∙ 8 ≤ B.a)? E) ?(2 ∙ A < A.a)? D

CompositeDifference : Compositor
    ∀ [A, B]
        C = A + B - 2 ∙ ((A ∙ B.a) ⋖ (B ∙ A.a))
        >> [C.a + A.a ∙ B.a, C.r, C.g, C.b]

CompositeExclusion : Compositor
    ∀ [A, B]
        C = A ∙ B.a + B ∙ A.a - 2 ∙ A ∙ B + A ⊕ B
        >> [C.a + A.a ∙ B.a, C.r, C.g, C.b]

CompositeSubtract : Compositor
    ∀ [A, B]
        >> (A + B - 1) ⋗ 0

CompositeInvert : Compositor
    ∀ [A, B]
        >> 1 - B
