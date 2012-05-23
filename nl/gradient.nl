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

BeginGradientColor () : Real >> (Real, Color)
    ∀ s
        >> (s, 0)

GradientSpan (A:Color, a:Real, B:Color, b:Real) : GradientColor
    ∀ (s, C)
        α = (b - s) / (b - a)
        C' = { αA + (1 - α)B, if a ≤ s ≤ b
               C,             otherwise    }
        >> (s, C')

EndGradientColor () : (Real, Color) >> Color
    ∀ (_, (r, g, b, α))
        >> (αr, αg, αb, α)

ApplyLinearGradient (A:Point, B:Point, e:GradientExtender, c:GradientColor) : Texturer
    → ProjectLinearGradient (A, B) → e → BeginGradientColor () → c → EndGradientColor ()

ApplyRadialGradient (A:Point, r:Real, e:GradientExtender, c:GradientColor) : Texturer
    → ProjectRadialGradient (A, r) → e → BeginGradientColor () → c → EndGradientColor ()
