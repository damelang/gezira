Color  <: (a, r, g, b : Real)
Point  <: (x, y : Real)
Vector <: (x, y : Real)
Matrix <: (a, b, c, d, e, f : Real)
Bezier <: (a, b, c : Point)
EdgeContribution <: (x, y, w, h : Real)

Sampler    :: Point >> Color
Compositor :: (Color, Color) >> Color

¬(a : Real) : Real
    a = 0

| (a : Real) | : Real
    { -a if a < 0, a }

(a : Real) ? (b : Real) : Real
    {a if a ≠ 0, b}

(a : Real) % (n : Real) : Real
    a - ⌊ a / (n ? 1) ⌋ × n

(a : Real) ◁ (b : Real) : Real
    {a if a < b, b}

(a : Real) ▷ (b : Real) : Real
    {a if a > b, b}

(a : Real) ~ (b : Real) : Real
    (a + b) / 2

(A : Point) #= (B : Point) : Real
    A.x = B.x ∧ A.y = B.y

(u : Vector) &= (v : Vector) : Real
    u.x = v.x ∧ u.y = v.y

(u : Vector) ?? (v : Vector) : Vector
    {u if ¬(u &= 0), v}

(u : Vector) ∙ (v : Vector) : Real
    u.x × v.x + u.y × v.y

‖ (u : Vector) ‖ : Real
    √(u ∙ u) 

^(u : Vector) : Vector
    {u / ‖ u ‖ if ‖ u ‖ ≠ 0, 0}

(A : Point) ⟂ (B : Point) : Vector
    ^(A.y - B.y, B.x - A.x)

(A : Point) ⇀ (B : Point) : Vector
    ^(B.x - A.x, B.y - A.y)

(M : Matrix) ⊗ (A : Point) : Point
    (M.a × A.x + M.c × A.y + M.e, M.b × A.x + M.d × A.y + M.f)

TransformPoints (M : Matrix) : Point >> Point
    ∀ P
        >> M ⊗ P

TransformBeziers (M : Matrix) : Bezier >> Bezier
    ∀ (A, B, C)
        >> (M ⊗ A, M ⊗ B, M ⊗ C)

UniformColor (c : Color) : Sampler
    ∀ P
        >> (c.a, c.a × c.r, c.a × c.g, c.a × c.b)

CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
    ⇒ Interleave (s1, s2) → c

CalculateBounds : Bezier >> (Point, Point)
    & (M, _, _)
    min = M
    max = M
    ∀ (A, B, C)
        min' = min ◁ A ◁ B ◁ C
        max' = max ▷ A ▷ B ▷ C
    >> (min, max)
