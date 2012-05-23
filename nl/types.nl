type Color  = (r:Real, g:Real, b:Real, α:Real)
type Point  = (x:Real, y:Real)
type Vector = (x:Real, y:Real)
type Matrix = (a:Real, b:Real, c:Real, d:Real, e:Real, f:Real)
type Bezier = (A:Point, B:Point, C:Point)
type EdgeSample    = (x:Real, y:Real, area:Real, height:Real)
type SpanCoverage  = (x:Real, y:Real, coverage:Real, length:Real)
type PointCoverage = (x:Real, y:Real, coverage:Real, icoverage:Real)

type Texturer         = Point >> Color
type Compositor       = (Color, Color) >> Color
type GradientExtender = Real >> Real
type GradientColor    = (Real, Color) >> (Real, Color)

a:Real² : Real
    aa

a:Real³ : Real
    aaa

|a:Real| : Real
    { -a, if a < 0
       a, otherwise }

|a:Integer| : Integer
    { -a, if a < 0
       a, otherwise }

-- TODO infer this?
|(a:Real, b:Real)| : (Real, Real)
    (|a|, |b|)

a:Real ? b:Real : Real
    { a, if a ≠ 0
      b, otherwise }

a:Integer ? b:Integer : Integer
    { a, if a ≠ 0
      b, otherwise }

a:Real ? b:Integer : Real
    b':Real = b
    a ? b'

a:Real % n:Integer : Real
    b = a / (n ? 1)
    a - ⌊b⌋n

(a1:Real, b1:Real) % n:Integer : (Real, Real)
    (a1 % n, b1 % n)

a:Real ◁ b:Real : Real
    { a, if a < b
      b, otherwise }

a:Integer ◁ b:Integer : Integer
    { a, if a < b
      b, otherwise }

a:Real ▷ b:Real : Real
    { a, if a > b
      b, otherwise }

A:Point = B:Point : Boolean
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 = x2 ∧ y1 = y2)

A:Point ≠ B:Point : Boolean
    ¬(A = B)

A:Point ≉ B:Point : Boolean
    ((x1, y1), (x2, y2)) = (A, B)
    x1 ≉ x2 ∨ y1 ≉ y1

A:Point ~ B:Point : Point
    ((x1, y1), (x2, y2)) = (A, B)
    ((x1 + x2) / 2, (y1 + y2) / 2)

A:Point - B:Point : Vector
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 - x2, y1 - y2)

A:Point - b:Real : Vector
    B:Point = (b, b)
    A - B

⌈A:Point⌉ : Point
    (x, y) = A
    (⌈x⌉, ⌈y⌉)

⌊A:Point⌋ : Point
    (x, y) = A
    (⌊x⌋, ⌊y⌋)

A:Point + b:Real : Point
    (x, y) = A
    (x + b, y + b)

A:Point + b:Integer : Point
    b':Real = b
    A + b'

A:Point - (x2:Real, y2:Real) : Vector
    B:Point = (x2, y2)
    A - B

A:Point + v:Vector : Point
    ((x1, y1), (x2, y2)) = (A, v)
    (x1 + x2, y1 + y2)

A:Point - v:Vector : Point
    ((x1, y1), (x2, y2)) = (A, v)
    (x1 - x2, y1 - y2)

a:Integer P:Point : Point
    (x, y) = P
    (ax, ay)

-u:Vector : Vector
    (x, y) = u
    (-x, -y)

u:Vector ≠ v:Vector : Boolean
    ((x1, y1), (x2, y2)) = (u, v)
    x1 ≠ x2 ∨ y1 ≠ y2

u:Vector ≠ r:Real : Boolean
    v:Vector = (r, r)
    u ≠ v

u:Vector ≠ i:Integer : Boolean
    i':Real = i
    u ≠ i'

u:Vector + v:Vector : Vector
    ((x1, y1), (x2, y2)) = (u, v)
    (x1 + y1, x2 + y2)

u:Vector + b:Real : Vector
    v:Vector = (b, b)
    u + v

a:Real v:Vector : Vector
    (x, y) = v
    (ax, ay)

u:Vector ? v:Vector : Vector
    { u, if u ≠ 0
      v, otherwise }

u:Vector ∙ v:Vector : Real
    ((x1, y1), (x2, y2)) = (u, v)
    x1 + x2

P:Point ∙ v:Vector : Real
    (x, y) = P
    u:Vector = (x, y)
    u ∙ v

|u:Vector| : Vector
    (x, y) = u
    (|x|, |y|)

‖u:Vector‖ : Real
    √(u ∙ u) 

⌊u:Vector⌋ : Vector
    (x, y) = u
    (⌊x⌋, ⌊y⌋)

u:Vector / s:Real : Vector
    (x, y) = u
    (x / s, y / s)

^u:Vector : Vector
    { u / ‖u‖, if ‖u‖ ≠ 0
      0,       otherwise  }

u:Vector < v:Vector : (Boolean, Boolean)
    ((x1, y1), (x2, y2)) = (u, v)
    (x1 < x2, y1 < y2)

u:Vector < r:Real : (Boolean, Boolean)
    v:Vector = (r, r)
    u < v

A:Point ⟂ B:Point : Vector
    ((x1, y1), (x2, y2)) = (A, B)
    v:Vector = (y1 - y2, x2 - x1)
    ^v

M:Matrix P:Point : Point
    (a, b, c, d, e, f) = M
    (x, y) = P
    (ax + cy + e, bx + dy + f)

A:Point ≤ B:Point : (Boolean, Boolean)
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 ≤ x2, y1 ≤ y2)

(a1:Boolean, b1:Boolean) ∧ (a2:Boolean, b2:Boolean) : (Boolean, Boolean)
    (a1 ∧ a2, b1 ∧ b2)

(a1:Boolean, b1:Boolean) ∨ (a2:Boolean, b2:Boolean) : (Boolean, Boolean)
    (a1 ∨ a2, b1 ∨ b2)

∧(a1:Boolean, a2:Boolean) : Boolean
    a1 ∧ a2

∨(a1:Boolean, a2:Boolean) : Boolean
    a1 ∨ a2

P:Point ≤ Z:Bezier : (Boolean, Boolean)
    (A, B, C) = Z
    P ≤ A ∧ P ≤ B ∧ P ≤ C

Z:Bezier ≤ P:Point : (Boolean, Boolean)
    (A, B, C) = Z
    A ≤ P ∧ B ≤ P ∧ C ≤ P

A:Point ▷ B:Point : Point
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 ▷ x2, y1 ▷ y2)

A:Point ◁ B:Point : Point
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 ◁ x2, y1 ◁ y2)

P:Point ▷ Z:Bezier : Bezier
    (A, B, C) = Z
    (P ▷ A, P ▷ B, P ▷ C)

Z:Bezier ◁ P:Point : Bezier
    (A, B, C) = Z
    (A ◁ P, B ◁ P, C ◁ P)

A:Color ◁ B:Color : Color
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1 ◁ r2, g1 ◁ g2, b1 ◁ b2, α1 ◁ α2)

A:Color ▷ B:Color : Color
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1 ▷ r2, g1 ▷ g2, b1 ▷ b2, α1 ▷ α2)

A:Color + B:Color : Color
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1 + r2, g1 + g2, b1 + b2, α1 + α2)

A:Color - B:Color : Color
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1 - r2, g1 - g2, b1 - b2, α1 - α2)

A:Color B:Color : Color
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1r2, g1g2, b1b2, α1α2)

A:Color / B:Color : Color
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1 / r2, g1 / g2, b1 / b2, α1 / α2)

A:Color < B:Color : (Boolean, Boolean, Boolean, Boolean)
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1 < r2, g1 < g2, b1 < b2, α1 < α2)

A:Color ≥ B:Color : (Boolean, Boolean, Boolean, Boolean)
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1 ≥ r2, g1 ≥ g2, b1 ≥ b2, α1 ≥ α2)

A:Color ≤ B:Color : (Boolean, Boolean, Boolean, Boolean)
    ((r1, g1, b1, α1), (r2, g2, b2, α2)) = (A, B)
    (r1 ≤ r2, g1 ≤ g2, b1 ≤ b2, α1 ≤ α2)

A:Color ≥ b:Real : (Boolean, Boolean, Boolean, Boolean)
    B:Color = (b, b, b, b)
    A ≥ B

A:Color ≤ b:Real : (Boolean, Boolean, Boolean, Boolean)
    B:Color = (b, b, b, b)
    A ≤ B

√A:Color : Color
    (r, g, b, α) = A
    (√r, √g, √b, √α)

a:Real B:Color : Color
    A:Color = (a, a, a, a)
    AB

A:Color b:Real : Color
    B:Color = (b, b, b, b)
    AB

A:Color ⊕ B:Color : Color
    (α, β) = (A.α, B.α)
    (1 - β)A + (1 - α)B

A:Color - b:Real : Color
    B:Color = (b, b, b, b)
    A - B

s:Integer C:Color : Color
    s':Real = s
    s'C

a:Real - B:Color : Color
    A:Color = (a, a, a, a)
    A - B

a:Integer - B:Color : Color
    a':Real = a
    a' - B

A:Color - b:Integer : Color
    b':Real = b
    A - b'

a:Real + B:Color : Color
    A:Color = (a, a, a, a)
    A + B

A:Color < b:Real : (Boolean, Boolean, Boolean, Boolean)
    B:Color  = (b, b, b, b)
    A < B

A:Color / b:Real : Color
    B:Color = (b, b, b, b)
    A / B

A:Color ◁ b:Real : Color
    B:Color = (b, b, b, b)
    A ◁ B

a:Real ▷ B:Color : Color
    A:Color = (a, a, a, a)
    A ▷ B

a:Real ◁ B:Color : Color
    A:Color = (a, a, a, a)
    A ◁ B

A:Color ◁ b:Integer : Color
    b':Real = b
    A ◁ b'

a:Integer ◁ B:Color : Color
    a':Real = a
    a' ◁ B

a:Real ◁ b:Integer : Real
    b':Real = b
    a ◁ b'

a:Integer ▷ B:Color : Color
    a':Real = a
    a' ▷ B

a:Integer ▷ b:Real : Real
    a':Real = a
    a' ▷ b

a:Real ▷ b:Integer : Real
    b':Real = b
    a ▷ b'

a:Integer ▷ (a2:Real, b2:Real) : (Real, Real)
    (a1, b1) = (a, a)
    (a1 ▷ a2, b1 ▷ b2)

(a1:Real, b1:Real) ◁ b:Integer : (Real, Real)
    (a2, b2) = (b, b)
    (a1 ◁ a2, b1 ◁ b2)
