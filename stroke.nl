StrokeJoin :: (o) Bezier >> Bezier
StrokeCap :: (o) Bezier >> Bezier

‖ p : Point ‖ : Real
    √(p.x ∙ p.x + p.y ∙ p.y) 

(a : Point ⟂ b : Point) : Point
    ab = b - a
    [0 - ab.y, ab.x] / ‖ ab ‖

StrokeCapButt : StrokeCap
    & [a, b, c]
        >> [a - (a ⟂ b) ∙ o, a, a + (a ⟂ b) ∙ o]

StrokeCapSquare : StrokeCap
    & [a, b, c]
        d = a - (a ⟂ b) ∙ o
        g = a + (a ⟂ b) ∙ o
        e = d + (a ⟂ g) ∙ o
        f = g + (a ⟂ g) ∙ o
        >> [d, d ~ e, e] >> [e, e ~ f, f] >> [f, f ~ g, g]

StrokeCapRound : StrokeCap
    & [a, b, c]
        -- TODO

StrokeJoinBevel : StrokeJoin
    % [a, b, c]
        ∀ [d, e, f]
            g = c + (b ⟂ c) ∙ o
            h = d + (d ⟂ e) ∙ o
            a', b', c' = d, e, f
            >> [g, g ~ h, h]

StrokeJoinMiter : StrokeJoin
    % [a, b, c]
        ∀ [d, e, f]
            g = c + (b ⟂ c) ∙ o
            i = d + (d ⟂ e) ∙ o
            -- TODO vector dot product is needed below
            h = c + ((b ⟂ c) ~ (d ⟂ e)) ∙ (o / ((b ⟂ c) ∙ (d ⟂ e)))
            a', b', c' = d, e, f
            >> [g, g ~ h, h] >> [h, h ~ i, i]

StrokeJoinRound : StrokeJoin
    % [a, b, c]
        ∀ [d, e, f]
            a', b', c' = d, e, f
            -- TODO

StrokeOffsetCurve (o) : Bezier >> Bezier
    ∀ [a, b, c]
        d = a + (a ⟂ b) ∙ o
        f = c + (b ⟂ c) ∙ o
        m = (a ~ b) ~ (b ~ c)
        n = m + ((a ⟂ b) ~ (b ⟂ c)) ∙ o
        e = 2 ∙ n - 0.5 ∙ d - 0.5 ∙ f
        error = ‖ (a ⟂ b) - (d ⟂ e) ‖ + ‖ (b ⟂ c) - (e ⟂ f) ‖
        if error < 0.1
            >> [d, e, f]
        else
            << [a, a ~ b, m] << [m, b ~ c, c]

StrokeSide (c : StrokeCap, j : StrokeJoin, o) : Bezier >> Bezier
    -> Mix (StrokeOffsetCurve (o), c (o), j (o))

StrokeReverseSide (c : StrokeCap, j : StrokeJoin, o) : Bezier >> Bezier
    -> ∀ [a, b, c]
           >> [c, b, a]
    -> Reverse -> StrokeSide (c, j, o)

Stroke (c : StrokeCap, j : StrokeJoin, o) : Bezier >> Bezier
    -> Mix (StrokeSide (c, j, o), StrokeReverseSide (c, j, o))
