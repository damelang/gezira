TransformPoints (M : Matrix) : Point >> Point
    ∀ P
        >> M ⊗ P

PadTexture (D : Point) : Point >> Point
    ∀ P
        >> 0 ▷ P ◁ D

RepeatTexture (D : Point) : Point >> Point
    ∀ P
        Q = P / D
        >> (Q - ⌊ Q ⌋) × D

ReflectTexture (D : Point) : Point >> Point
    ∀ P
        Q = P / D
        >> | (| Q - 1 | % 2 - 1) | × D

UniformColor (C : Color) : Texture
    D = (C.a, C.a × C.r, C.a × C.g, C.a × C.b)
    ∀ _
        >> D

CompositeTextures (t1 : Texture, t2 : Texture, c : Compositor) : Texture
    ⇒ DupZip (t1, t2) → c

ExpandSpans : CoverageSpan >> CoveragePoint
    ∀ (x, y, c, l)
        if c > 0 ∧ l > 0
            >> (x,     y, c, 1 - c)
            << (x + 1, y, c, l - 1)

ExtractSamplePoints : CoveragePoint >> Point
    ∀ (x, y, _, _)
        >> (x, y)

ApplyTexture (t : Texture) : CoverageSpan >> (Color, CoveragePoint)
    ⇒ ExpandSpans → DupZip (ExtractSamplePoints → t, (→))
