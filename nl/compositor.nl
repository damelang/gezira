CompositeClear () : Compositor
    ∀ (A, B)
        >> 0

CompositeSrc () : Compositor
    ∀ (A, B)
        >> A

CompositeDst () : Compositor
    ∀ (A, B)
        >> B

CompositeOver () : Compositor
    ∀ (A, B)
        α = A.α
        >> A + (1 - α)B 

CompositeDstOver () : Compositor
    ∀ (A, B)
        β = B.α
        >> B + (1 - β)A 

CompositeSrcIn () : Compositor
    ∀ (A, B)
        β = B.α
        >> βA 

CompositeDstIn () : Compositor
    ∀ (A, B)
        α = A.α
        >> αB

CompositeSrcOut () : Compositor
    ∀ (A, B)
        β = B.α
        >> (1 - β)A 

CompositeDstOut () : Compositor
    ∀ (A, B)
        α = A.α
        >> (1 - α)B 

CompositeSrcAtop () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        >> βA + (1 - α)B 

CompositeDstAtop () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        >> αB + (1 - β)A

CompositeXor () : Compositor
    ∀ (A, B)
        >> A ⊕ B

CompositePlus () : Compositor
    ∀ (A, B)
        >> (A + B) ◁ 1

CompositeMultiply () : Compositor
    ∀ (A, B)
        >> AB + (A ⊕ B)

CompositeScreen () : Compositor
    ∀ (A, B)
        >> A + B - AB

CompositeOverlay () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        C = 2AB + (A ⊕ B)
        D = αβ - 2(β - B)(α - A) + (A ⊕ B)
        >> { C, if 2B < β
             D, otherwise }

CompositeDarken () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        >> (βA ◁ αB) + (A ⊕ B)

CompositeLighten () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        >> (βA ▷ αB) + (A ⊕ B)

CompositeColorDodge () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        C = αβ + (A ⊕ B)
        D = αB / (1 - A / α) + (A ⊕ B)
        >> { C,     if βA + αB ≥ αβ
             D ◁ 1, otherwise       }

CompositeColorBurn () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        C = βA + αB
        D = α(C - αβ) / A + (A ⊕ B)
        >> { A ⊕ B, if C ≤ αβ
             D,     otherwise }

CompositeHardLight () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        C = 2AB + (A ⊕ B)
        D = αβ - 2(β - B)(α - A) + (A ⊕ B)
        >> { C, if 2A < α
             D, otherwise }

CompositeSoftLight () : Compositor
    ∀ (A, B)
        (α, β) = (A.α, B.α)
        C = (1 - B / β)(2A - α)
        D = B(α - C) + (A ⊕ B)
        E = B(α - C(3 - 8B / β)) + (A ⊕ B)
        F = αB + (√(B / β)β - B)(2A - α) + (A ⊕ B)
        >> { D, if 2A < α
             E, if 8B ≤ β
             F, otherwise }

CompositeDifference () : Compositor
    ∀ (A, B)
        (α, β)       = (A.α, B.α)
        (r, g, b, γ) = A + B - 2(βA ◁ αB)
        >> (r, g, b, αβ + γ)

CompositeExclusion () : Compositor
    ∀ (A, B)
        (α, β)       = (A.α, B.α)
        (r, g, b, γ) = βA + αB - 2AB + (A ⊕ B)
        >> (r, g, b, αβ + γ)

CompositeSubtract () : Compositor
    ∀ (A, B)
        >> 0 ▷ (A + B - 1)

CompositeInvert () : Compositor
    ∀ (A, B)
        (r, g, b, α) = B
        >> (1 - r, 1 - g, 1 - b, α)

InverseOver (β:Real) : Color >> Color
    ∀ A
        (r, g, b, α) = A
        α' = α ? 1
        A':Color = (r / α', g / α', b / α', α')
        (r', g', b', _) = (1 - β)A' + β(1 - A')
        >> (αr', αg', αb', α)
