PixelCoverage <: (x, y, c, ic : Real)

ExpandSpans : EdgeSpan >> PixelCoverage
    ∀ (x, y, c, l)
        if c
            >> (x, y, c, 1 - c)
        if l > 0
            << (x + 1, y, 1, l - 1)

ExtractSamplePoints : PixelCoverage >> Point
    ∀ (x, y, _, _)
        >> (x, y)

ApplyTexture (t : Texture) : EdgeSpan >> (Color, PixelCoverage)
    ⇒ ExpandSpans → DupZip (ExtractSamplePoints → t, (→))
