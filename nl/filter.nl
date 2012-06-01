SumWeightedColors (n:Number) : (Number, Color) >> Color
    (i, sum:Color) = (1, 0)
    ∀ (w, C)
        if i = n
            (i', sum') = (1, 0)
            >> 0 ▷ (sum + wC) ◁ 1
        else
            (i', sum') = (i + 1, sum + wC)

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
        (w1, w2) = (\cubic|Δx|, \cubic|Δy|)
        >> w1w2

BicubicFilter (t:Texturer) : Texturer
    → DupZip (→ BicubicFilterDeltas () → BicubicFilterWeights (),
              → BicubicFilterPoints () → t) →
      SumWeightedColors (16)
