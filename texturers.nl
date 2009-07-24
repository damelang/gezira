CombineTexturers (t1 : Texturer, t2 : Texturer, c : Compositor) : Texturer
    -> Interleave (t1 (x, y, i), t2 (x, y, i)) -> c

UniformColor (c : Color) : Texturer
    ∀ _
        >> c

LinearGradient (sl, dl/dx, dl/dy : Real) : (x, y : Real) : AlphaCoverage >> Real
    l = sl + x ∙ dl/dx  + y ∙ dl/dy
    ∀ _
        >> l
        l' <- l + dl/dx

GradientPad : Real >> Real
    ∀ l
        >> 0 .> l <. 1

GradientRepeat : Real >> Real
    ∀ l
        >> l - ⌊ l ⌋

GradientMirror : Real >> Real
    ∀ l
        >> 1 - | (| l | % 2 - 1) |

BeginGradientColor : Real >> [Real, Color]
    ∀ l
        >> [l, [0, 0, 0, 0]]

GradientColorSpan (stop, dc/dl : Color, ll : Real) : [Real, Color] >> [Real, Color]
    ∀ [l, c]
        d = stop + l ∙ dc/dl
        >> [l - ll, d ?(l < 0)? c]

EndGradientColor : [Real, Color] >> Color
    ∀ [_, c]
        >> c
