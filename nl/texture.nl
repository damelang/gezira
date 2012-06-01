TransformPoints (M:Matrix) : Point >> Point
    ∀ P
        >> MP

PadTexture (w:Number, h:Number) : Point >> Point
    ∀ (x, y)
        T      = (x / w, y / h)
        (s, t) = 0 ▷ T ◁ 1
        >> (sw, th)

RepeatTexture (w:Number, h:Number) : Point >> Point
    ∀ (x, y)
        T      = (x / w, y / h)
        (s, t) = T - ⌊T⌋
        >> (sw, th)

ReflectTexture (w:Number, h:Number) : Point >> Point
    ∀ (x, y)
        T      = (x / w, y / h)
        (s, t) = |(|(T - 1)| % 2 - 1)|
        >> (sw, th)

UniformColor (C:Color) : Texturer
    (r, g, b, α) = C
    D = (αr, αg, αb, α)
    ∀ _
        >> D

CompositeTexturers (t1:Texturer, t2:Texturer, c:Compositor) : Texturer
    → DupZip (t1, t2) → c

ExpandSpans () : SpanCoverage >> PointCoverage
    ∀ (x, y, c, l)
        if c > 0 ∧ l > 0
            >> (x, y, c, 1 - c)
            << (x + 1, y, c, l - 1)

ExtractSamplePoints () : PointCoverage >> Point
    ∀ (x, y, _, _)
        >> (x, y)

ApplyTexturer (t:Texturer) : SpanCoverage >> (Color, PointCoverage)
    → ExpandSpans () → DupZip (→ ExtractSamplePoints () → t,
                               → PassThrough ())
