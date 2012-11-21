example
exampleBounds
	"GeziraBindings exampleBounds"
	| bounds vertices g target transform rectangle |
	vertices := GeziraCanvas star.
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
	target := Form extent: 400@300 depth: 32.
	"draw star"
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g transformBeziers: transform.
				g clipBeziers: target boundingBox.
				g rasterize.
				g compositeUniformColorCA: 1 cR: 1 cG: 0 cB: 0 overImageARGB32: target});
		pour: vertices from: 1 to: vertices size final: true;
		sync.
	"draw bounds"
	rectangle := (bounds first@bounds second corner: bounds third@bounds fourth) asGeziraPath.
	(g := GeziraBindings new)
		kernels: (
			 g pipeline: {
				g funnel.
				g strokeBezierPathW: 2 l: 4 c: 0.
				g clipBeziers: target boundingBox.
				g rasterize.
				g compositeUniformColorCA: 1 cR: 0 cG: 0 cB: 1 overImageARGB32: target});
		pour: rectangle from: 1 to: rectangle size final: true;
		sync.
	Display getCanvas translucentImage: target at: 0@0.
