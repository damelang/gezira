StrokeJoin :: (o : Real) Bezier >> Bezier
StrokeCap :: (o : Real) Bezier >> Bezier

(‖ p : Point ‖) : Real
    √(p.x ∙ p.x + p.y ∙ p.y) 

(⟂ p : Point) : Point
    [0 - p.y, p.x]

(^ p : Point) : Point
    p / ‖ p ‖

StrokeCapButt : StrokeCap
    %$ [a, b, c]
        ab = ^(b - a)
        >> [a - ⟂(ab) ∙ o, a, a + ⟂(ab) ∙ o]

StrokeJoinBevel : StrokeJoin
    % [a, b, c]
    ∀ [d, e, f]
        bc = ^(c - b)
        de = ^(e - d)
        f  = c + ⟂(bc) ∙ o
        g  = d + ⟂(de) ∙ o
        h  = d - ⟂(de) ∙ o
        i  = c - ⟂(bc) ∙ o
        >> [f, f ~~ g, g] >> [h, h ~~ i, i]
        a', b', c' = d, e, f

StrokeOutline (o : Real) : Bezier >> Bezier
    ∀ [a, b, c]
        ab = ^(b - a)
        bc = ^(c - b)
        d = a + ⟂(ab) ∙ o
        f = c + ⟂(bc) ∙ o
        m = (a ~~ b) ~~ (b ~~ c)
        n = m + (⟂(ab) ~~ ⟂(bc)) ∙ o
        e = -0.5 ∙ d + 2 ∙ n - 0.5 ∙ f
        de = ^(e - d)
        ef = ^(f - e)
        error = ‖ ef - bc ‖ + ‖ de - ab ‖
        if error < 0.1
            >> [d, e, f]
        else
            << [a, a ~~ b, m] << [m, b ~~ c, c]

StrokeOutlineReverse (o : Real) : Bezier >> Bezier
    -> ∀ [a, b, c]
           >> [c, b, a]
    -> StrokeOutline (o)

Stroke (o : Real, j : StrokeJoin, c : StrokeCap) : Bezier >> Bezier
    -> Mix (StrokeOutline (o), StrokeOutlineReverse (o), j (o), c (o))
