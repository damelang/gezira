-- TODO declare that Real and ColorComponent are built-in primitive types
-- TODO declare that Image is an built-in opaque type
-- TODO declare that WriteImage and ReadImage are built-in kernels
---   of type (Real, Real, Image) Color >>| and Texturer

-- TODO these should be vector subclasses
Point <: [x, y : Real]
Bezier <: [A, B, C : Point]
Color <: [a, r, g, b : ColorComponent]
EdgeContribution <: [x, y, w, h : Real]
Matrix <: [a, b, c, d, e, f : Real]

-- TODO these should be type aliases
Texturer <: (x, y : Real, i : Image) : ColorComponent >> Color
Compositor <: [Color, Color] >> Color
GradientShape <: (x, y : Real) : AlphaCoverage >> Real
GradientExtend <: Real >> Real
GradientColor <: [Real, Color] >> [Real, Color]
