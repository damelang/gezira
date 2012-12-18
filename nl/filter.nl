SumWeightedColors (n:Number) : (Number, Color) >> Color
    i = 1
    sum:Color = (0, 0, 0, 0)
    ∀ (w, C)
        i' = { 1,     if i = n
               i + 1, otherwise }
        sum' = { (0, 0, 0, 0), if i = n
                 sum + wC,     otherwise }
        if i = n
            >> 0 ▷ (sum + wC) ◁ 1

BilinearFilterPoints () : Point >> Point
    ∀ P
        (x, y) = ⌊(P - 0.5)⌋ + 0.5
        >> (x, y    ) >> (x + 1, y    )
        >> (x, y + 1) >> (x + 1, y + 1)

BilinearFilterWeights () : Point >> Number
    ∀ P 
        (x, y) = ⌊(P - 0.5)⌋ + 0.5
        (u, v) = P - (x, y)
        >> (1 - u) (1 - v) >> u (1 - v)
        >> (1 - u) (    v) >> u (    v)

BilinearFilter (t:Texturer) : Texturer
    → DupZip (→ BilinearFilterWeights (),
              → BilinearFilterPoints  () → t) →
      SumWeightedColors (4)

BicubicFilterPoints () : Point >> Point
    ∀ P
        (x, y) = ⌊(P - 0.5)⌋ + 0.5
        >> (x - 1, y - 1) >> (x, y - 1) >> (x + 1, y - 1) >> (x + 2, y - 1)
        >> (x - 1, y    ) >> (x, y    ) >> (x + 1, y    ) >> (x + 2, y    )
        >> (x - 1, y + 1) >> (x, y + 1) >> (x + 1, y + 1) >> (x + 2, y + 1)
        >> (x - 1, y + 2) >> (x, y + 2) >> (x + 1, y + 2) >> (x + 2, y + 2)

BicubicFilterDeltas () : Point >> Vector
    ∀ P 
        (x, y) = ⌊(P - 0.5)⌋ + 0.5
        >> P - (x - 1, y - 1) >> P - (x, y - 1) >> P - (x + 1, y - 1) >> P - (x + 2, y - 1)
        >> P - (x - 1, y    ) >> P - (x, y    ) >> P - (x + 1, y    ) >> P - (x + 2, y    )
        >> P - (x - 1, y + 1) >> P - (x, y + 1) >> P - (x + 1, y + 1) >> P - (x + 2, y + 1)
        >> P - (x - 1, y + 2) >> P - (x, y + 2) >> P - (x + 1, y + 2) >> P - (x + 2, y + 2)

\cubic(s:Number) : Number
    {  1.5s³ - 2.5s²      + 1, if 0 ≤ s < 1
      -0.5s³ + 2.5s² - 4s + 2, if 1 ≤ s < 2
                            0, otherwise    }

BicubicFilterWeights () : Vector >> Number
    ∀ (Δx, Δy)
        (w1, w2) = (\cubic(|Δx|), \cubic(|Δy|))
        >> w1w2

BicubicFilter (t:Texturer) : Texturer
    → DupZip (→ BicubicFilterDeltas () → BicubicFilterWeights (),
              → BicubicFilterPoints () → t) →
      SumWeightedColors (16)

GaussianBlur11x1Points () : Point >> Point
    ∀ (x, y)
        >> (x - 5, y) >> (x - 4, y) >> (x - 3, y) >> (x - 2, y) >> (x - 1, y)
        >> (x    , y)
        >> (x + 1, y) >> (x + 2, y) >> (x + 3, y) >> (x + 4, y) >> (x + 5, y)

GaussianBlur1x11Points () : Point >> Point
    ∀ (x, y)
        >> (x, y - 5) >> (x, y - 4) >> (x, y - 3) >> (x, y - 2) >> (x, y - 1)
        >> (x, y    )
        >> (x, y + 1) >> (x, y + 2) >> (x, y + 3) >> (x, y + 4) >> (x, y + 5)

GaussianBlur11x1Weights (f:Number) : Point >> Number
    a = 1024f
    s = 1024 + 11a
    ∀ _
        >> (a +   1) / s >> (a +  10) / s >> (a +  45) / s
        >> (a + 120) / s >> (a + 210) / s >> (a + 252) / s
        >> (a + 210) / s >> (a + 120) / s >> (a +  45) / s
        >> (a +  10) / s >> (a +   1) / s

GaussianBlur11x1 (f:Number, t:Texturer) : Texturer
    → DupZip (→ GaussianBlur11x1Weights (f),
              → GaussianBlur11x1Points () → t) → SumWeightedColors (11)

GaussianBlur1x11 (f:Number, t:Texturer) : Texturer
    → DupZip (→ GaussianBlur11x1Weights (f), 
              → GaussianBlur1x11Points () → t) → SumWeightedColors (11)
