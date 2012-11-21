example
example
	"GeziraBindings example"
	| target vertices g |
	target := Form extent: 400@300 depth: 32.
	vertices := GeziraCanvas star.
	(g := GeziraBindings new)
			kernels: (g pipeline: {
				g funnel.
				g transformBeziers: (MatrixTransform2x3 withOffset: 150@150).
				g clipBeziers: target boundingBox.
				g rasterize.
				g compositeUniformColorCA: 0.5 cR: 1 cG: 0 cB: 0 overImageARGB32: target });
		pour: vertices from: 1 to: vertices size final: true;
		sync.
	Display getCanvas translucentImage: target at: 0@0
