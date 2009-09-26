StrokeJoin :: (o) Bezier >> Bezier
StrokeCap :: (o) Bezier >> Bezier

‖ a : Point ‖ : Real
    √(a.x × a.x + a.y × a.y) 

^(a : Point) : Point
    if ‖ a ‖ ≠ 0
        a / ‖ a ‖
    else
        a

(a : Point ⟂ b : Point) : Point
    c = b - a
    [0 - ^(c).y, ^(c).x]

(a : Point ~ b : Point ~ c : Point) : Point
    y = (a ~ c) - b
    z = ^(y) ?(‖ y ‖ ≠ 0)? a ⟂ b
    b + z × ‖ a - b ‖

(a : Point $ b : Point $ c : Point) : Point
    2 × b - 0.5 × a - 0.5 × c

StrokeCapButt : StrokeCap
    & [a, b, c]
        >> [a - (a ⟂ b) × o, a, a + (a ⟂ b) × o]

StrokeCapSquare : StrokeCap
    & [a, b, c]
        d = a - (a ⟂ b) × o
        g = a + (a ⟂ b) × o
        e = d + (a ⟂ g) × o
        f = g + (a ⟂ g) × o
        >> [d, d ~ e, e] >> [e, e ~ f, f] >> [f, f ~ g, g]

StrokeCapRound : StrokeCap
    & [a, b, c]
        -- TODO, reuse StrokeJoinRound

StrokeJoinBevel : StrokeJoin
    % [a, b, c]
        ∀ [d, e, f]
            g = c + (b ⟂ c) × o
            h = d + (d ⟂ e) × o
            a', b', c' = d, e, f
            >> [g, g ~ h, h]

StrokeJoinMiter : StrokeJoin
    % [a, b, c]
        ∀ [d, e, f]
            -- TODO
            a', b', c' = d, e, f

StrokeJoinRound : StrokeJoin
    % [a, b, c]
        ∀ [d, e, f]
            a', b', c' = d, e, f
            g = c + (b ⟂ c) × o
            k = c + (d ⟂ e) × o
            i = g ~c~ k
            h = g ~c~ i
            j = i ~c~ k
            >> [g, g $(g ~c~ h)$ h, h]
            >> [h, h $(h ~c~ i)$ i, i]
            >> [i, i $(i ~c~ j)$ j, j]
            >> [j, j $(j ~c~ k)$ k, k]

StrokeOffsetCurve (o) : Bezier >> Bezier
    ∀ [a, b, c]
        d = a + (a ⟂ b) × o
        f = c + (b ⟂ c) × o
        m = (a ~ b) ~ (b ~ c)
        n = m + ((a ⟂ b) ~ (b ⟂ c)) × o
        e = 2 × n - 0.5 × d - 0.5 × f
        error = ‖ (a ⟂ b) - (d ⟂ e) ‖ + ‖ (b ⟂ c) - (e ⟂ f) ‖
        if error < 0.1
            >> [d, e, f]
        else
            << [a, a ~ b, m] << [m, b ~ c, c]

StrokeSide (c : StrokeCap, j : StrokeJoin, o) : Bezier >> Bezier
    ➔ Mix (StrokeOffsetCurve (o), c (o), j (o))

StrokeReverseSide (c : StrokeCap, j : StrokeJoin, o) : Bezier >> Bezier
    ➔ ∀ [a, b, c]
           >> [c, b, a]
    ➔ Reverse ➔ StrokeSide (c, j, o)

Stroke (c : StrokeCap, j : StrokeJoin, o) : Bezier >> Bezier
    ➔ Mix (StrokeSide (c, j, o), StrokeReverseSide (c, j, o))
