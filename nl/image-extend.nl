ImageExtendMode :: (D : Point) : Point >> Point

ImageExtendPad : ImageExtendMode
    ∀ P
        >> 0 ▷ P ◁ D

ImageExtendRepeat : ImageExtendMode
    ∀ P
        Q = P / D
        >> (Q - ⌊ Q ⌋) × D

ImageExtendReflect : ImageExtendMode
    ∀ P
        Q = P / D
        >> | (| Q - 1 | % 2 - 1) | × D
