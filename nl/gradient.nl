GradientShape :: Point >> Real
GradientExtendMode :: Real >> Real
GradientColor :: (Real, Color) >> (Real, Color)

LinearGradientShape (s00, dsdx, dsdy : Real) : GradientShape
    ∀ (x, y)
        >> s00 + x × dsdx + y × dsdy

RadialGradientShape (C : Point, r : Real) : GradientShape
    ∀ P
        >> ‖ P - C ‖ / r

GradientExtendPad : GradientExtendMode
    ∀ s
        >> 0 ▷ s ◁ 1

GradientExtendRepeat : GradientExtendMode
    ∀ s
        >> s - ⌊ s ⌋

GradientExtendReflect : GradientExtendMode
    ∀ s
        >> | (| s - 1 | % 2 - 1) |

GradientColorBegin : Real >> (Real, Color)
    ∀ s
        >> (s, 0)

GradientColorSpan (c0, dcds : Color, l : Real) : GradientColor
    ∀ (s, c)
        d = c0 + s × dcds
        >> (s - l, {c if s < 0, d})

GradientColorEnd : (Real, Color) >> Color
    ∀ (_, c)
        >> (c.a, c.a × c.r, c.a × c.g, c.a × c.b)

Gradient (s : GradientShape, m : GradientExtendMode, c : GradientColor) : Texture
    ⇒ s → m → GradientColorBegin → c → GradientColorEnd
