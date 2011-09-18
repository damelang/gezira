CompositeClear : Compositor
    ∀ (A, B)
        >> 0

CompositeSrc : Compositor
    ∀ (A, B)
        >> A

CompositeDst : Compositor
    ∀ (A, B)
        >> B

CompositeOver : Compositor
    ∀ (A, B)
        >> A + B × (1 - A.a)

CompositeDstOver : Compositor
    ∀ (A, B)
        >> B + A × (1 - B.a)

CompositeSrcIn : Compositor
    ∀ (A, B)
        >> A × B.a

CompositeDstIn : Compositor
    ∀ (A, B)
        >> B × A.a

CompositeSrcOut : Compositor
    ∀ (A, B)
        >> A × (1 - B.a)

CompositeDstOut : Compositor
    ∀ (A, B)
        >> B × (1 - A.a)

CompositeSrcAtop : Compositor
    ∀ (A, B)
        >> A × B.a + B × (1 - A.a)

CompositeDstAtop : Compositor
    ∀ (A, B)
        >> B × A.a + A × (1 - B.a)

CompositeXor : Compositor
    ∀ (A, B)
        >> A ⊕ B

CompositePlus : Compositor
    ∀ (A, B)
        >> (A + B) ◁ 1

CompositeMultiply : Compositor
    ∀ (A, B)
        >> A × B + (A ⊕ B)

CompositeScreen : Compositor
    ∀ (A, B)
        >> A + B - A × B

CompositeOverlay : Compositor
    ∀ (A, B)
        C = 2 × A × B + (A ⊕ B)
        D = A.a × B.a - 2 × (B.a - B) × (A.a - A) + (A ⊕ B)
        >> {C if 2 × B < B.a, D}

CompositeDarken : Compositor
    ∀ (A, B)
        >> (A × B.a) ◁ (B × A.a) + (A ⊕ B)

CompositeLighten : Compositor
    ∀ (A, B)
        >> (A × B.a) ▷ (B × A.a) + (A ⊕ B)

CompositeColorDodge : Compositor
    ∀ (A, B)
        C = A.a × B.a + (A ⊕ B)
        D = (B × A.a / (1 - A / A.a) + (A ⊕ B)) ◁ 1
        >> {C if A × B.a + B × A.a ≥ A.a × B.a, D}

CompositeColorBurn : Compositor
    ∀ (A, B)
        c = A.a × (A × B.a + B × A.a - A.a × B.a) / A + (A ⊕ B)
        >> {A ⊕ B if A × B.a + B × A.a ≤ A.a × B.a, c}

CompositeHardLight : Compositor
    ∀ (A, B)
        C = 2 × A × B + (A ⊕ B)
        D = A.a × B.a - 2 × (B.a - B) × (A.a - A) + (A ⊕ B)
        >> {C if 2 × A < A.a, D}

CompositeSoftLight : Compositor
    ∀ (A, B)
        C = (1 - B / B.a) × (2 × A - A.a)
        D = B × (A.a - C) + (A ⊕ B)
        E = B × (A.a - C × (3 - 8 × B / B.a)) + (A ⊕ B)
        F = B × A.a + (√(B / B.a) × B.a - B) × (2 × A - A.a) + (A ⊕ B)
        >> {D if 2 × A < A.a, E if B × 8 ≤ B.a, F}

CompositeDifference : Compositor
    ∀ (A, B)
        C = A + B - 2 × ((A × B.a) ◁ (B × A.a))
        >> (C.a + A.a × B.a, C.r, C.g, C.b)

CompositeExclusion : Compositor
    ∀ (A, B)
        C = A × B.a + B × A.a - 2 × A × B + (A ⊕ B)
        >> (C.a + A.a × B.a, C.r, C.g, C.b)

CompositeSubtract : Compositor
    ∀ (A, B)
        >> (A + B - 1) ▷ 0

CompositeInvert : Compositor
    ∀ (A, B)
        >> (B.a, 1 - B.r, 1 - B.g, 1 - B.b)

InverseOver (A : Real) : Color >> Color
    ∀ C
        D = C / (C.a ? 1)
        E = A × (1 - D) + (1 - A) × D
        >> (C.a, C.a × E.r, C.a × E.g, C.a × E.b)

ContrastiveOver (a : Real) : Color >> Color
    ∀ C
        D = C / (C.a ? 1)
        E = (1, {1/2 if D.r < 1/4, 0  },
                {5/8 if D.g < 1/2, 3/8},
                {1   if D.b < 3/4, 1/2}) : Color
        F = (1 - a) × D + a × E
        >> (C.a, C.a × F.r, C.a × F.g, C.a × F.b)
