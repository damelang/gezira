-- Real, ColorComponent are scalar types
Point <: [x, y : Real]
Color <: [a, r, g, b : ColorComponent]
EdgeContribution <: [p : Point, w, h : Real]

Alpha :: ColorComponent
Sampler :: (start : Point) : _ >> Color
Canvas :: (start : Point) : [Color, Alpha] >>|
Compositor :: [Color, Color] >> Color
