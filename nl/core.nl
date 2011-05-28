Color    <: (a, r, g, b : Real)
Point    <: (x, y : Real)
Vector   <: (x, y : Real)
Matrix   <: (a, b, c, d, e, f : Real)
Bezier   <: (A, B, C : Point)
EdgeSpan <: (x, y, c, l : Real)

Texture    :: Point >> Color
Compositor :: (Color, Color) >> Color

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

(u : Vector) ≠* (v : Vector) : Real
    u.x ≠ v.x ∨ u.y ≠ v.y

(u : Vector) ?? (v : Vector) : Vector
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

TransformPoints (M : Matrix) : Point >> Point
    ∀ P
        >> M ⊗ P

TransformBeziers (M : Matrix) : Bezier >> Bezier
    ∀ (A, B, C)
        >> (M ⊗ A, M ⊗ B, M ⊗ C)

UniformColor (C : Color) : Texture
    ∀ _
        >> (C.a, C.a × C.r, C.a × C.g, C.a × C.b)

CompositeTextures (t1 : Texture, t2 : Texture, c : Compositor) : Texture
    ⇒ DupZip (t1, t2) → c

CalculateBounds : Bezier >> (Point, Point)
    min =  999999 : Point
    max = -999999 : Point
    ∀ (A, B, C)
        min' = min ◁ A ◁ B ◁ C
        max' = max ▷ A ▷ B ▷ C
    >> (min, max)

RectangleSpans (min, max : Point) : Real >> EdgeSpan
    l = max.x - min.x - 1
    x = min.x + 0.5
    << min.y + 0.5
    ∀ y
        if y < max.y
            >> (x, y, 1, l)
            << y + 1
