ImageExtendMode :: Point >> Point

ImageExtendPad (D : Point) : ImageExtendMode
    ∀ P
        >> 0 ▷ P ◁ D

ImageExtendRepeat (D : Point) : ImageExtendMode
    ∀ P
        Q = P / D
        >> (Q - ⌊ Q ⌋) × D

ImageExtendReflect (D : Point) : ImageExtendMode
    ∀ P
        Q = P / D
        >> | (| Q - 1 | % 2 - 1) | × D
