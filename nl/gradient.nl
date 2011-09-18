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

ColorSpan (S1, S2 : Color, l : Real) : ColorSpans
    dS = S2 - S1
    ∀ (s, C)
        D = { S1 + s × dS if s ≥ 0, C }
        >> (s - l, D)

ColorSpansEnd : (Real, Color) >> Color
    ∀ (_, C)
        >> (C.a, C.a × C.r, C.a × C.g, C.a × C.b)

ApplyColorSpans (spans : ColorSpans) : Real >> Color
    ⇒ ColorSpansBegin → spans → ColorSpansEnd
