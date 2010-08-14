SumWeightedColors (n : Real) : (Color, Real) >> Color
    sum = 0 : Color
    i   = 1
    ∀ (c, w)
        if i = n
            >> 0 ▷ (sum + c × w) ◁ 1
            sum' = 0
            i'   = 1
        else
            sum' = sum + c × w
            i'   = i + 1

BilinearFilterPoints : Point >> Point
    ∀ P
        S = ⌊ P - 0.5 ⌋ + 0.5
        x = S.x
        y = S.y
        >> (x, y    ) >> (x + 1, y    )
        >> (x, y + 1) >> (x + 1, y + 1)

BilinearFilterWeights : Point >> Real
    ∀ P 
        S = P - ⌊ P - 0.5 ⌋ - 0.5
        u = S.x
        v = S.y
        >> (1 - u) × (1 - v) >> u × (1 - v)
        >> (1 - u) × (    v) >> u × (    v)

BilinearFilter (s : Sampler) : Sampler
    ⇒ Interleave (BilinearFilterPoints → s,
                  BilinearFilterWeights    ) → SumWeightedColors (4)

KeysWeights : Point >> Real
    ∀ D
        T = |D|
        S = {  1.5 × T × T × T - 2.5 × T × T + 1           if T < 1,
              -0.5 × T × T × T + 2.5 × T × T - 4 × T + 2   if T < 2,
                 0                                                  }
        >> S.x × S.y

BicubicFilterPoints : Point >> Point
    ∀ P
        S = ⌊ P - 0.5 ⌋ + 0.5
        x = S.x
        y = S.y
        >> (x-1, y-1) >> (x, y-1) >> (x+1, y-1) >> (x+2, y-1)
        >> (x-1, y  ) >> (x, y  ) >> (x+1, y  ) >> (x+2, y  )
        >> (x-1, y+1) >> (x, y+1) >> (x+1, y+1) >> (x+2, y+1)
        >> (x-1, y+2) >> (x, y+2) >> (x+1, y+2) >> (x+2, y+2)

BicubicFilterDeltas : Point >> Point
    ∀ P 
        S = ⌊ P - 0.5 ⌋ + 0.5
        x = S.x
        y = S.y
        >> (x-1, y-1) - P >> (x, y-1) - P >> (x+1, y-1) - P >> (x+2, y-1) - P
        >> (x-1, y  ) - P >> (x, y  ) - P >> (x+1, y  ) - P >> (x+2, y  ) - P
        >> (x-1, y+1) - P >> (x, y+1) - P >> (x+1, y+1) - P >> (x+2, y+1) - P
        >> (x-1, y+2) - P >> (x, y+2) - P >> (x+1, y+2) - P >> (x+2, y+2) - P

BicubicFilter (s : Sampler) : Sampler
    ⇒ Interleave (BicubicFilterPoints → s,
                  BicubicFilterDeltas → KeysWeights) → SumWeightedColors (16)
