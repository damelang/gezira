TransformBeziers (M:Matrix) : Bezier >> Bezier
    ∀ (A, B, C)
        >> (MA, MB, MC)

ClipBeziers (min:Point, max:Point) : Bezier >> Bezier
    ϵ = 0.1
    ∀ Z
        if ∧(min ≤ Z ≤ max)
            >> Z
        else if ∨(Z ≤ min ∨ max ≤ Z)
            >> min ▷ Z ◁ max
        else
            (A, B, C)    = Z
            M            = (A ~ B) ~ (B ~ C)
            (Δmin, Δmax) = (M - min, M - max)
            edge         = { min,  if |Δmin| < |Δmax|
                             max,  otherwise          }
            Δedge        = M - edge
            N            = { edge, if |Δedge| < ϵ
                             M,    otherwise      }
            << (N, B ~ C, C) << (A, A ~ B, N) 

CalculateBounds () : Bezier >> (Point, Point)
    (min:Point, max:Point) = ((∞, ∞), (-∞, -∞))
    ∀ (A, B, C)
        min' = { min ◁ A ◁ B ◁ C, if ¬(A.y = B.y = C.y)
                 min,             otherwise             }
        max' = { max ▷ A ▷ B ▷ C, if ¬(A.y = B.y = C.y)
                 max,             otherwise             }
    >> (min, max)
