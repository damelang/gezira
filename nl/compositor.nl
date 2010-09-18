(a : Color) ⊕ (b : Color) : Color
    a × (1 - b.a) + b × (1 - a.a)

CompositeClear : Compositor
    ∀ (a, b)
        >> 0

CompositeSrc : Compositor
    ∀ (a, b)
        >> a

CompositeDst : Compositor
    ∀ (a, b)
        >> b

CompositeOver : Compositor
    ∀ (a, b)
        >> a + b × (1 - a.a)

CompositeDstOver : Compositor
    ∀ (a, b)
        >> b + a × (1 - b.a)

CompositeSrcIn : Compositor
    ∀ (a, b)
        >> a × b.a

CompositeDstIn : Compositor
    ∀ (a, b)
        >> b × a.a

CompositeSrcOut : Compositor
    ∀ (a, b)
        >> a × (1 - b.a)

CompositeDstOut : Compositor
    ∀ (a, b)
        >> b × (1 - a.a)

CompositeSrcAtop : Compositor
    ∀ (a, b)
        >> a × b.a + b × (1 - a.a)

CompositeDstAtop : Compositor
    ∀ (a, b)
        >> b × a.a + a × (1 - b.a)

CompositeXor : Compositor
    ∀ (a, b)
        >> a ⊕ b

CompositePlus : Compositor
    ∀ (a, b)
        >> (a + b) ◁ 1

CompositeMultiply : Compositor
    ∀ (a, b)
        >> a × b + (a ⊕ b)

CompositeScreen : Compositor
    ∀ (a, b)
        >> a + b - a × b

CompositeOverlay : Compositor
    ∀ (a, b)
        c = 2 × a × b + (a ⊕ b)
        d = a.a × b.a - 2 × (b.a - b) × (a.a - a) + (a ⊕ b)
        >> {c if 2 × b < b.a, d}

CompositeDarken : Compositor
    ∀ (a, b)
        >> (a × b.a) ◁ (b × a.a) + (a ⊕ b)

CompositeLighten : Compositor
    ∀ (a, b)
        >> (a × b.a) ▷ (b × a.a) + (a ⊕ b)

CompositeColorDodge : Compositor
    ∀ (a, b)
        c = a.a × b.a + (a ⊕ b)
        d = (b × a.a / (1 - a / a.a) + (a ⊕ b)) ◁ 1
        >> {c if a × b.a + b × a.a ≥ a.a × b.a, d}

CompositeColorBurn : Compositor
    ∀ (a, b)
        c = a.a × (a × b.a + b × a.a - a.a × b.a) / a + (a ⊕ b)
        >> {a ⊕ b if a × b.a + b × a.a ≤ a.a × b.a, c}

CompositeHardLight : Compositor
    ∀ (a, b)
        c = 2 × a × b + (a ⊕ b)
        d = a.a × b.a - 2 × (b.a - b) × (a.a - a) + (a ⊕ b)
        >> {c if 2 × a < a.a, d}

CompositeSoftLight : Compositor
    ∀ (a, b)
        c = (1 - b / b.a) × (2 × a - a.a)
        d = b × (a.a - c) + (a ⊕ b)
        e = b × (a.a - c × (3 - 8 × b / b.a)) + (a ⊕ b)
        f = b × a.a + (√(b / b.a) × b.a - b) × (2 × a - a.a) + (a ⊕ b)
        >> {d if 2 × a < a.a, e if b × 8 ≤ b.a, f}

CompositeDifference : Compositor
    ∀ (a, b)
        c = a + b - 2 × ((a × b.a) ◁ (b × a.a))
        >> (c.a + a.a × b.a, c.r, c.g, c.b)

CompositeExclusion : Compositor
    ∀ (a, b)
        c = a × b.a + b × a.a - 2 × a × b + (a ⊕ b)
        >> (c.a + a.a × b.a, c.r, c.g, c.b)

CompositeSubtract : Compositor
    ∀ (a, b)
        >> (a + b - 1) ▷ 0

CompositeInvert : Compositor
    ∀ (a, b)
        >> (b.a, 1 - b.r, 1 - b.g, 1 - b.b)

InverseOver (a : Real) : Color >> Color
    ∀ C
        D = C / (C.a ? 1)
        E = a × (1 - D) + (1 - a) × D
        >> (C.a, C.a × E.r, C.a × E.g, C.a × E.b)

ContrastiveOver (a : Real) : Color >> Color
    ∀ C
        D = C / (C.a ? 1)
        E = (1, {0.5 if D.r < 0.25, 0},
                 0.5,
                {1   if D.b < 0.75, 0.5}) : Color
        F = (1 - a) × D + a × E
        >> (C.a, C.a × F.r, C.a × F.g, C.a × F.b)
