Color    <: (a, r, g, b : Real)
Point    <: (x, y : Real)
Vector   <: (x, y : Real)
Matrix   <: (a, b, c, d, e, f : Real)
Bezier   <: (A, B, C : Point)
EdgeSample <: (x, y, a, h : Real)
EdgeSpan   <: (x, y, c, l : Real)
PixelCoverage <: (x, y, c, ic : Real)

Texture    :: Point >> Color
Compositor :: (Color, Color) >> Color
ColorSpans :: (Real, Color) >> (Real, Color)

¬(a : Real) : Real
    a = 0

| (a : Real) | : Real
    { -a if a < 0, a }

(a : Real) ? (b : Real) : Real
    { a if a ≠ 0, b }

(a : Real) % (n : Real) : Real
    a - ⌊ a / (n ? 1) ⌋ × n

(a : Real) ◁ (b : Real) : Real
    { a if a < b, b }

(a : Real) ▷ (b : Real) : Real
    { a if a > b, b }

(a : Real) ~ (b : Real) : Real
    (a + b) / 2

(A : Color) ⊕ (B : Color) : Color
    A × (1 - B.a) + B × (1 - A.a)

(u : Vector) ≠* (v : Vector) : Real
    u.x ≠ v.x ∨ u.y ≠ v.y

(u : Vector) ?* (v : Vector) : Vector
    { u if u ≠* 0, v }

(u : Vector) ∙ (v : Vector) : Real
    u.x × v.x + u.y × v.y

‖ (u : Vector) ‖ : Real
    √(u ∙ u)

^(u : Vector) : Vector
    { u / ‖ u ‖ if ‖ u ‖ ≠ 0, 0 }

(A : Point) ⟂ (B : Point) : Vector
    ^(A.y - B.y, B.x - A.x)

(M : Matrix) ⊗ (A : Point) : Point
    (M.a × A.x + M.c × A.y + M.e, M.b × A.x + M.d × A.y + M.f)
