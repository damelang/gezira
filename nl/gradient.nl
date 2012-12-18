ProjectLinearGradient (A:Point, B:Point) : Point >> Number
    v   = B - A
    Δs  = v / (v ∙ v)
    s00 = A ∙ Δs
    ∀ P
        >> P ∙ Δs - s00

ProjectRadialGradient (C:Point, r:Number) : Point >> Number
    ∀ P
        >> ‖(P - C)‖ / r

PadGradient () : GradientExtender
    ∀ s
        >> 0 ▷ s ◁ 1

RepeatGradient () : GradientExtender
    ∀ s
        >> s - ⌊s⌋

ReflectGradient () : GradientExtender
    ∀ s
        >> |(|(s - 1)| % 2 - 1)|

-- For two-stop gradients:

SingleGradientSpan (A:Color, B:Color) : Number >> Color
    ∀ α
        >> αA + (1 - α)B

ApplySingleLinearGradient (S1:ColorStop, S2:ColorStop, e:GradientExtender) : Texturer
    → ProjectLinearGradient (S1.P, S2.P) → e → SingleGradientSpan (S1.C, S2.C)

ApplySingleRadialGradient (S1:ColorStop, S2:ColorStop, r:Number, e:GradientExtender) : Texturer
    r = ‖(S2.P - S1.P)‖
    → ProjectRadialGradient (S1.P, r) → e → SingleGradientSpan (S1.C, S2.C)

-- For two-or-more-stop gradients

BeginGradientSpans () : Number >> (Number, Color)
    ∀ s
        >> (s, (0, 0, 0, 0))

GradientSpan (a:Number, A:Color, b:Number, B:Color) : GradientSpan
    ∀ (s, C)
        α = (b - s) / (b - a)
        D = { αA + (1 - α)B, if a ≤ s ≤ b
              C,             otherwise    }
        >> (s, D)

EndGradientSpans () : (Number, Color) >> Color
    ∀ (_, (r, g, b, α))
        >> (αr, αg, αb, α)

ApplyLinearGradient (A:Point, B:Point, e:GradientExtender, spans:GradientSpan) : Texturer
    → ProjectLinearGradient (A, B) → e → BeginGradientSpans () → spans → EndGradientSpans ()

ApplyRadialGradient (A:Point, B:Point, e:GradientExtender, spans:GradientSpan) : Texturer
    r = ‖(B - A)‖
    → ProjectRadialGradient (A, r) → e → BeginGradientSpans () → spans → EndGradientSpans ()
