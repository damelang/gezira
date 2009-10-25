ImageExtendMode :: (size : Point) Point >> Point
GradientShape :: Point >> Real
GradientExtendMode :: Real >> Real
GradientColor :: [Real, Color] >> [Real, Color]

FilterBegin : Point >> Point
    ∀ [x, y]
        >>                  [x, y + 0.5]
        >> [x - 0.5, y]  >> [x, y      ] >> [x + 0.5, y]
        >>                  [x, y - 0.5]

{- FilterEnd : Color >> Color
    ∀ a, b, c, d, e
        >> (a + b + c + c + d + e) / 6
-} 

FilterEnd : Color >> Color
    sum : Color = 0
    n = 1
    ∀ c
        if n = 6
            >> (sum + c) / n
            sum' = 0
            n' = 1
        else
            if i = 3
                sum' = sum + c + c
            else
                sum' = sum + c
            n' = n + 1

FilterSampler (s : Sampler) : Sampler
    ⇒ FilterBegin → s → FilterEnd

TransformSample (m : Matrix) : Point >> Point
    ∀ p
        >> m × p

ImageExtendPad : ImageExtendMode
    ∀ p
        >> 0 ⋗ (p - 0.5) ⋖ (size - 1)

ImageExtendRepeat : ImageExtendMode
    ∀ p
        q = (p - 0.5) / size
        >> (q - ⌊ q ⌋) × size

ImageExtendMirror : ImageExtendMode
    ∀ p
        q = | p - 0.5 | % (2 × size) - size
        >> size - | q |

LinearGradientShape (s00, ds/dx, ds/dy) : GradientShape
    ∀ [x, y]
        >> s00 + x × ds/dx + y × ds/dy

RadialGradientShape (c : Point, r) : GradientShape
    ∀ p
        d = p - c
        >> √(d.x × d.x + d.y × d.y) / r

GradientPad : GradientExtendMode
    ∀ s
        >> 0 ⋗ s ⋖ 1

GradientRepeat : GradientExtendMode
    ∀ s
        >> s - ⌊ s ⌋

GradientMirror : GradientExtendMode
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
    ∀ [s, c]
        >> [c.a, c.r × c.a, c.g × c.a, c.b × c.a]

Gradient (s : GradientShape, e : GradientExtendMode, c : GradientColor) : Sampler
    ⇒ s → e → GradientColorBegin → c → GradientColorEnd
