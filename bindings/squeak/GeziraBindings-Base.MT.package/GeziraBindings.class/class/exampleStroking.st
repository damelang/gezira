example
exampleStroking
	"GeziraBindings exampleStroking"
	| target vertices g |
	target := Form extent: 400@300 depth: 32.
	vertices := GeziraCanvas star.
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g transformBeziers: (MatrixTransform2x3 withOffset: 150@150).
				g strokeBezierPathW: 10 l: 4 c: 0.
				g clipBeziers: target boundingBox.
				g rasterize.
				g  compositeUniformColorCA: 1 cR: 0 cG: 0 cB: 1 overImageARGB32: target});
		pour: vertices asFloatArray from: 1 to: vertices size final: true;
		sync.
	Display getCanvas translucentImage: target at: 0@0
