CombineTexturers (t1 : Texturer, t2 : Texturer, c : Compositor) : Texturer
    -> Interleave (t1 (x, y, i), t2 (x, y, i)) -> c

UniformColor (c : Color) : Texturer
    ∀ _
        >> c

LinearGradient (s00, ds/dx, ds/dy : Real) : GradientShape
    s = s00 + x ∙ ds/dx  + y ∙ ds/dy
    ∀ _
        s' = s + ds/dx
        >> s

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
        >> [s, [0, 0, 0, 0]]

GradientColorSpan (c0, dc/ds : Color, l : Real) : GradientColor
    ∀ [s, c]
        d = c0 + s ∙ dc/ds
        >> [s - l, d ?(s < 0)? c]

GradientColorEnd : [Real, Color] >> Color
    ∀ [_, c]
        >> c

Gradient (s : GradientShape, e : GradientExtend, c : GradientColor) : Texturer
    -> s (x, y) -> e -> GradientColorBegin -> c -> GradientColorEnd
