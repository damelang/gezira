ProjectLinearGradient (A:Point, B:Point) : Point >> Real
    v   = B - A
    Δs  = v / (v ∙ v)
    s00 = A ∙ Δs
    ∀ P
        >> P ∙ Δs - s00

ProjectRadialGradient (A:Point, r:Real) : Point >> Real
    ∀ P
        >> ‖(P - A)‖ / r

PadGradient () : GradientExtender
    ∀ s
        >> 0 ▷ s ◁ 1

RepeatGradient () : GradientExtender
    ∀ s
        >> s - ⌊s⌋

ReflectGradient () : GradientExtender
    ∀ s
        >> |(|(s - 1)| % 2 - 1)|

GradientSpan (A:Color, a:Real, B:Color, b:Real) : Real >> Color
    ∀ s
        t = (b - s) / (b - a)
        (r, g, b, α) = tA + (1 - t)B
        >> (αr, αg, αb, α)
