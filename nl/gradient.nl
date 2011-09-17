LinearGradient (s00, dsdx, dsdy : Real) : Point >> Real
    ∀ (x, y)
        >> s00 + x × dsdx + y × dsdy

RadialGradient (C : Point, r : Real) : Point >> Real
    ∀ P
        >> ‖ P - C ‖ / r

PadGradient : Real >> Real
    ∀ s
        >> 0 ▷ s ◁ 1

RepeatGradient : Real >> Real
    ∀ s
        >> s - ⌊ s ⌋

ReflectGradient : Real >> Real
    ∀ s
        >> | (| s - 1 | % 2 - 1) |

ColorSpansBegin : Real >> (Real, Color)
    ∀ s
        >> (s, 0)

ColorSpan (c0, dcds : Color, l : Real) : ColorSpans
    ∀ (s, c)
        d = c0 + s × dcds
        >> (s - l, {c if s < 0, d})

ColorSpansEnd : (Real, Color) >> Color
    ∀ (_, c)
        >> (c.a, c.a × c.r, c.a × c.g, c.a × c.b)

ApplyColorSpans (spans : ColorSpans) : Real >> Color
    ⇒ ColorSpansBegin → spans → ColorSpansEnd
