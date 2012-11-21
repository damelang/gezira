example
exampleSoftShadow
	"GeziraBindings exampleSoftShadow"
	| bounds vertices g target shadowOffset blurWidth blurFlattenFactor transform shadowForm shadowColor boundsPath blurForm |
	vertices := GeziraCanvas star.
	shadowColor := Color black alpha: 0.5.
	shadowOffset := 2@5.
	blurWidth := 11.
	blurFlattenFactor := 1.
	transform := MatrixTransform2x3 withOffset: 150@150.
	transform := transform composedWithLocal: (MatrixTransform2x3 withAngle: 20).

	"get bounds"
	bounds := FloatArray new: 4.
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g transformBeziers: transform.
				g calculateBounds.
				g capture: bounds});
		pour: vertices from: 1 to: vertices size final: true;
		sync.
	bounds := bounds first@bounds second corner: bounds third@bounds fourth.
	bounds := bounds expandBy: blurWidth + 1 // 2.
	boundsPath := (0@0 extent: bounds extent) asGeziraPath.

	"render object into shadow form"
	shadowForm := Form extent: bounds extent depth: 32.
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g transformBeziers: transform.
				g transformBeziers: (MatrixTransform2x3 withOffset: bounds topLeft negated).
				g clipBeziers: shadowForm boundingBox.
				g rasterize.
				g compositeUniformColorCA: shadowColor alpha cR: shadowColor red cG: shadowColor green cB: shadowColor blue overImageARGB32: shadowForm});
		pour: vertices from: 1 to: vertices size final: true;
		sync.

	"blur shadow horizontally"
	blurForm := Form extent: bounds extent depth: 32.
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g clipBeziers: blurForm boundingBox.
				g rasterize.
				g applyTextureT: (g gaussianBlur11x1F: blurFlattenFactor t: (
					g readFromImageARGB32: shadowForm)).
				g writeToImageARGB32: blurForm});
		pour: boundsPath from: 1 to: boundsPath size final: true;
		sync.

	"blur shadow vertically"
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g clipBeziers: shadowForm boundingBox.
				g rasterize.
				g applyTextureT: (g gaussianBlur1x11F: blurFlattenFactor t: (
					g readFromImageARGB32: blurForm)).
				g writeToImageARGB32: shadowForm});
		pour: boundsPath from: 1 to: boundsPath size final: true;
		sync.

	"draw shadow"
	target := Form extent: 400@300 depth: 32.
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g transformBeziers: (MatrixTransform2x3 withOffset: bounds topLeft + shadowOffset).
				g clipBeziers: target boundingBox.
				g rasterize.
				g applyTextureT: (g pipeline: {
					g transformPoints: (MatrixTransform2x3 withOffset: (bounds topLeft + shadowOffset) negated).
					g readFromImageARGB32: shadowForm.
				}).
				g writeToImageARGB32: target});
		pour: boundsPath from: 1 to: boundsPath size final: true;
		sync.
	"draw object"
	(g := GeziraBindings new)
		kernels: (g pipeline: {
			g funnel.
			g transformBeziers: transform.
			g clipBeziers: target boundingBox.
			g rasterize.
			g compositeUniformColorCA: 1 cR: 1 cG: 0 cB: 0 overImageARGB32: target});
		pour: vertices from: 1 to: vertices size final: true;
		sync.
	"show result"
	Display getCanvas translucentImage: target at: 0@0.
