ProjectLinearGradient (A:Point, B:Point) : Point >> Number
    v   = B - A
    Δs  = v / (v ∙ v)
    s00 = A ∙ Δs
    ∀ P
        >> P ∙ Δs - s00

ProjectRadialGradient (A:Point, r:Number) : Point >> Number
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

BeginGradientColor () : Number >> (Number, Color)
    ∀ s
        >> (s, 0)

GradientSpan (A:Color, a:Number, B:Color, b:Number) : GradientColor
    ∀ (s, C)
        α = (b - s) / (b - a)
        D = { αA + (1 - α)B, if a ≤ s ≤ b
              C,             otherwise    }
        >> (s, D)

EndGradientColor () : (Number, Color) >> Color
    ∀ (_, (r, g, b, α))
        >> (αr, αg, αb, α)

ApplyLinearGradient (A:Point, B:Point, e:GradientExtender, c:GradientColor) : Texturer
    → ProjectLinearGradient (A, B) → e → BeginGradientColor () → c → EndGradientColor ()

ApplyRadialGradient (A:Point, r:Number, e:GradientExtender, c:GradientColor) : Texturer
    → ProjectRadialGradient (A, r) → e → BeginGradientColor () → c → EndGradientColor ()
