ImageExtendMode :: (w, h : Real) : Point >> Point
GradientShape :: Point >> Real
GradientExtendMode :: Real >> Real
GradientColor :: (Real, Color) >> (Real, Color)

FilterBegin : Point >> Point
    ∀ (x, y)
        >>                  (x, y + 0.6)
        >> (x - 0.6, y)  >> (x, y      ) >> (x + 0.6, y)
        >>                  (x, y - 0.6)

{- FilterEnd : Color >> Color
    ∀ a, b, c, d, e
        >> (a + b + c + c + d + e) / 6
-} 

FilterEnd : Color >> Color
    n = 1
    sum = 0 : Color
    ∀ c
        if n = 5
            n'   = 1
            sum' = 0
            >> (sum + c) / 6
        else
            n'   = n + 1
            sum' = {sum + c + c if n = 3, sum + c}

FilterSampler (s : Sampler) : Sampler
    ⇒ FilterBegin → s → FilterEnd

TransformPoints (M : Matrix) : Point >> Point
    ∀ P
        >> M ⊗ P

GradientExtendPad : GradientExtendMode
    ∀ s
        >> 0 ⋗ s ⋖ 1

ImageExtendPad : ImageExtendMode
    D = (w, h)
    ∀ P
        >> 0 ⋗ P ⋖ D

GradientExtendRepeat : GradientExtendMode
    ∀ s
        >> s - ⌊ s ⌋

ImageExtendRepeat : ImageExtendMode
    D = (w, h)
    ∀ P
        Q = P / D
        >> (Q - ⌊ Q ⌋) × D

GradientExtendReflect : GradientExtendMode
    ∀ s
        >> | (| s - 1 | % 2 - 1) |

ImageExtendReflect : ImageExtendMode
    D = (w, h)
    ∀ P
        Q = P / D
        >> | (| Q - 1 | % 2 - 1) | × D

LinearGradientShape (s00, dsdx, dsdy : Real) : GradientShape
    ∀ (x, y)
        >> s00 + x × dsdx + y × dsdy

RadialGradientShape (C : Point, r : Real) : GradientShape
    ∀ P
        >> ‖ P - C ‖ / r

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

Gradient (s : GradientShape, e : GradientExtendMode, c : GradientColor) : Sampler
    ⇒ s → e → GradientColorBegin → c → GradientColorEnd
