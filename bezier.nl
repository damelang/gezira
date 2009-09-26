(m : Matrix × p : Point) : Point
    [m.a × p.x + m.c × p.y + m.e,
     m.b × p.x + m.d × p.y + m.f]

TransformBezier (m : Matrix) : Bezier >> Bezier
    ∀ [a, b, c]
        >> [m × a, m × b, m × c]

ClipBezier (min, max : Point) : Bezier >> Bezier
    ∀ [a, b, c]
        bmin = a ⋖ b ⋖ c
        bmax = a ⋗ b ⋗ c
        if ∧[ min ≤ bmin ∧ bmax ≤ max ]
            >> [a, b, c]
        else if ∨[ bmax ≤ min ∨ max ≤ bmin ]
            ca = min ⋗ a ⋖ max
            cc = min ⋗ c ⋖ max
            >> [ca, ca ~ cc, cc]
        else 
            abbc    = (a ~ b) ~ (b ~ c)
            nearmin = | abbc - min | < 0.1
            nearmax = | abbc - max | < 0.1
            m       = min ?(nearmin)? (max ?(nearmax)? abbc)
            << [a, a ~ b, m] << [m, b ~ c, c]

DecomposeBezier : Bezier >> EdgeContribution
    ∀ [a, b, c]
        if ∧[ ⌊ a ⌋ = ⌊ c ⌋ ∨ ⌈ a ⌉ = ⌈ c ⌉ ]
            p = ⌊ a ⌋ ⋖ ⌊ c ⌋
            w = p.x + 1 - (c.x ~ a.x)
            h = c.y - a.y
            >> [p, w, h]
        else
            abbc    = (a ~ b) ~ (b ~ c)
            min     = ⌊ abbc ⌋
            max     = ⌈ abbc ⌉
            nearmin = | abbc - min | < 0.1
            nearmax = | abbc - max | < 0.1
            m       = min ?(nearmin)? (max ?(nearmax)? abbc)
            << [a, a ~ b, m] << [m, b ~ c, c]
