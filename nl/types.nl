type Color  = (r:Number, g:Number, b:Number, α:Number)
type Point  = (x:Number, y:Number)
type Vector = (x:Number, y:Number)
type Matrix = (a:Number, b:Number, c:Number, d:Number, e:Number, f:Number)
type Bezier = (A:Point, B:Point, C:Point)
type EdgeSample    = (x:Number, y:Number, area:Number, height:Number)
type SpanCoverage  = (x:Number, y:Number, coverage:Number, length:Number)
type PointCoverage = (x:Number, y:Number, coverage:Number, icoverage:Number)

type Texturer         = Point >> Color
type Compositor       = (Color, Color) >> Color
type GradientExtender = Number >> Number
type GradientColor    = (Number, Color) >> (Number, Color)

a:Number² : Number
    aa

a:Number³ : Number
    aaa

|a:Number| : Number
    { -a, if a < 0
       a, otherwise }

a:Number ≈ b:Number : Boolean
    |(a - b)| < 0.0001

a:Number ≉ b:Number : Boolean
    ¬(a ≈ b)

a:Number ? b:Number : Number
    { a, if a ≠ 0
      b, otherwise }

a:Number % n:Number : Number
    b = a / (n ? 1)
    a - ⌊b⌋n

a:Number ◁ b:Number : Number
    { a, if a < b
      b, otherwise }

a:Number ▷ b:Number : Number
    { a, if a > b
      b, otherwise }

A:Point = B:Point : Boolean
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 = x2 ∧ y1 = y2)

A:Point ≈ B:Point : Boolean
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 ≈ x2 ∧ y1 ≈ y2)

A:Point ≠ B:Point : Boolean
    ¬(A = B)

A:Point ≉ B:Point : Boolean
    ¬(A ≈ B)

A:Point ≤ B:Point : (Boolean, Boolean)
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 ≤ x2, y1 ≤ y2)

A:Point - B:Point : Vector
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 - x2, y1 - y2)

⌈A:Point⌉ : Point
    (x, y) = A
    (⌈x⌉, ⌈y⌉)

⌊A:Point⌋ : Point
    (x, y) = A
    (⌊x⌋, ⌊y⌋)

A:Point ~ B:Point : Point
    ((x1, y1), (x2, y2)) = (A, B)
    ((x1 + x2) / 2, (y1 + y2) / 2)

A:Point ▷ B:Point : Point
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 ▷ x2, y1 ▷ y2)

A:Point ◁ B:Point : Point
    ((x1, y1), (x2, y2)) = (A, B)
    (x1 ◁ x2, y1 ◁ y2)

A:Point + v:Vector : Point
    ((x1, y1), (x2, y2)) = (A, v)
    (x1 + x2, y1 + y2)

A:Point - v:Vector : Point
    ((x1, y1), (x2, y2)) = (A, v)
    (x1 - x2, y1 - y2)

A:Point + b:Number : Point
    v:Vector = (b, b)
    A + v

A:Point - b:Number : Point
    v:Vector = (b, b)
    A - v

A:Point - (x2:Number, y2:Number) : Vector
    B:Point = (x2, y2)
    A - B

-u:Vector : Vector
    (x, y) = u
    (-x, -y)

u:Vector ≠ v:Vector : Boolean
    ((x1, y1), (x2, y2)) = (u, v)
    x1 ≠ x2 ∨ y1 ≠ y2

u:Vector ≠ s:Number : Boolean
    v:Vector = (s, s)
    u ≠ v

u:Vector + v:Vector : Vector
    ((x1, y1), (x2, y2)) = (u, v)
    (x1 + y1, x2 + y2)

u:Vector + b:Number : Vector
    v:Vector = (b, b)
    u + v

a:Number v:Vector : Vector
    (x, y) = v
    (ax, ay)

u:Vector ? v:Vector : Vector
    { u, if u ≠ 0
      v, otherwise }

u:Vector ∙ v:Vector : Number
    ((x1, y1), (x2, y2)) = (u, v)
    x1x2 + y1y2

P:Point ∙ v:Vector : Number
    (x, y) = P
    u:Vector = (x, y)
    u ∙ v

|u:Vector| : Vector
    (x, y) = u
    (|x|, |y|)

‖u:Vector‖ : Number
    √(u ∙ u) 

⌊u:Vector⌋ : Vector
    (x, y) = u
    (⌊x⌋, ⌊y⌋)

u:Vector / s:Number : Vector
    (x, y) = u
    (x / s, y / s)

u:Vector < v:Vector : (Boolean, Boolean)
    ((x1, y1), (x2, y2)) = (u, v)
    (x1 < x2, y1 < y2)

u:Vector < r:Number : (Boolean, Boolean)
    v:Vector = (r, r)
    u < v

A:Point ⟂ B:Point : Vector
    ((x1, y1), (x2, y2)) = (A, B)
    v:Vector = (y1 - y2, x2 - x1)
    { v / ‖v‖, if ‖v‖ ≠ 0
      0,       otherwise  }

M:Matrix P:Point : Point
    (a, b, c, d, e, f) = M
    (x, y) = P
    (ax + cy + e, bx + dy + f)

(a1:Boolean, b1:Boolean) ∧ (a2:Boolean, b2:Boolean) : (Boolean, Boolean)
    (a1 ∧ a2, b1 ∧ b2)

P:Point ≤ Z:Bezier : (Boolean, Boolean)
    (A, B, C) = Z
    P ≤ A ∧ P ≤ B ∧ P ≤ C

Z:Bezier ≤ P:Point : (Boolean, Boolean)
    (A, B, C) = Z
    A ≤ P ∧ B ≤ P ∧ C ≤ P

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

A:Color ≥ b:Number : (Boolean, Boolean, Boolean, Boolean)
    B:Color = (b, b, b, b)
    A ≥ B

A:Color ≤ b:Number : (Boolean, Boolean, Boolean, Boolean)
    B:Color = (b, b, b, b)
    A ≤ B

√A:Color : Color
    (r, g, b, α) = A
    (√r, √g, √b, √α)

a:Number B:Color : Color
    A:Color = (a, a, a, a)
    AB

A:Color b:Number : Color
    B:Color = (b, b, b, b)
    AB

A:Color ⊕ B:Color : Color
    (α, β) = (A.α, B.α)
    (1 - β)A + (1 - α)B

A:Color - b:Number : Color
    B:Color = (b, b, b, b)
    A - B

a:Number - B:Color : Color
    A:Color = (a, a, a, a)
    A - B

a:Number + B:Color : Color
    A:Color = (a, a, a, a)
    A + B

A:Color < b:Number : (Boolean, Boolean, Boolean, Boolean)
    B:Color  = (b, b, b, b)
    A < B

A:Color / b:Number : Color
    B:Color = (b, b, b, b)
    A / B

A:Color ◁ b:Number : Color
    B:Color = (b, b, b, b)
    A ◁ B

a:Number ▷ B:Color : Color
    A:Color = (a, a, a, a)
    A ▷ B

a:Number ◁ B:Color : Color
    A:Color = (a, a, a, a)
    A ◁ B

-- TODO infer these?

⌊(a:Number, b:Number)⌋ : (Number, Number)
    (⌊a⌋, ⌊b⌋)

(a1:Number, b1:Number) - (a2:Number, b2:Number) : (Number, Number)
    (a1 - a2, b1 - b2)

(a1:Number, b1:Number) - n:Number : (Number, Number)
    (a1, b1) - (n, n)

|(a:Number, b:Number)| : (Number, Number)
    (|a|, |b|)

(a1:Number, b1:Number) % n:Number : (Number, Number)
    (a1 % n, b1 % n)

n:Number ▷ (a2:Number, b2:Number) : (Number, Number)
    (a1, b1) = (n, n)
    (a1 ▷ a2, b1 ▷ b2)

(a1:Number, b1:Number) ◁ n:Number : (Number, Number)
    (a2, b2) = (n, n)
    (a1 ◁ a2, b1 ◁ b2)

(a1:Boolean, b1:Boolean) ∨ (a2:Boolean, b2:Boolean) : (Boolean, Boolean)
    (a1 ∨ a2, b1 ∨ b2)

∧(a1:Boolean, a2:Boolean) : Boolean
    a1 ∧ a2

∨(a1:Boolean, a2:Boolean) : Boolean
    a1 ∨ a2
