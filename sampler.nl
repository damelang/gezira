ImageExtendMode :: (w, h : Real) Point >> Point
GradientShape :: Point >> Real
GradientExtendMode :: Real >> Real
GradientColor :: (Real, Color) >> (Real, Color)

FilterBegin : Point >> Point
    ∀ (x, y)
        >>                  (x, y + 0.5)
        >> (x - 0.5, y)  >> (x, y      ) >> (x + 0.5, y)
        >>                  (x, y - 0.5)

{- FilterEnd : Color >> Color
    ∀ a, b, c, d, e
        >> (a + b + c + c + d + e) / 6
-} 

FilterEnd : Color >> Color
    n = 1
    sum : Color = 0
    ∀ c
        if n = 6
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
        >> M × P

ImageExtendPad : ImageExtendMode
    D = (w, h)
    ∀ P
        >> 0 ⋗ P ⋖ D

ImageExtendRepeat : ImageExtendMode
    D = (w, h)
    ∀ P
        Q = P / D
        >> (Q - ⌊ Q ⌋) × D

ImageExtendReflect : ImageExtendMode
    D = (w, h)
    ∀ P
        Q = | P / D | % 2 - 1
        >> (1 - | Q |) × D

GradientExtendPad : GradientExtendMode
    ∀ s
        >> 0 ⋗ s ⋖ 1

GradientExtendRepeat : GradientExtendMode
    ∀ s
        >> s - ⌊ s ⌋

GradientExtendReflect : GradientExtendMode
    ∀ s
        t = | s | % 2 - 1
        >> 1 - | t |

LinearGradientShape (s00, dsdx, dsdy : Real) : GradientShape
    ∀ (x, y)
        >> s00 + x × dsdx + y × dsdy

RadialGradientShape (C : Point, r : Real) : GradientShape
    ∀ P
        >> ‖ P ⇀ C ‖ / r

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
