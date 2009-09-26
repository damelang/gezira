GradientShape :: (start : Point) : Real >> Real
GradientExtend :: Real >> Real
GradientColor :: [Real, Color] >> [Real, Color]

LinearGradient (s00, ds/dx, ds/dy) : GradientShape
    s = s00 + start.x × ds/dx + start.y × ds/dy
    ∀ _
        s' = s + ds/dx
        >> s

RadialGradient (c : Point, r) : GradientShape
    x = start.x
    dy² = (start.y - c.y) × (start.y - c.y)
    ∀ _
        x' = x + 1
        >> √((x - c.x) × (x - c.x) + dy²) / r

GradientPad : GradientExtend
    ∀ s
        >> 0 ⋗ s ⋖ 1

GradientRepeat : GradientExtend
    ∀ s
        >> s - ⌊ s ⌋

GradientMirror : GradientExtend
    ∀ s
        >> 1 - | (| s | % 2 - 1) |

GradientColorBegin : Real >> [Real, Color]
    ∀ s
        >> [s, 0]

GradientColorSpan (c0, dc/ds : Color, l) : GradientColor
    ∀ [s, c]
        d = c0 + s × dc/ds
        >> [s - l, c ?(s < 0)? d]

GradientColorEnd : [Real, Color] >> Color
    ∀ [_, c]
        >> [c.a, c.r × c.a, c.g × c.a, c.b × c.a]

Gradient (s : GradientShape, e : GradientExtend, c : GradientColor) : Sampler
    ➔ s (start) ➔ e ➔ GradientColorBegin ➔ c ➔ GradientColorEnd
