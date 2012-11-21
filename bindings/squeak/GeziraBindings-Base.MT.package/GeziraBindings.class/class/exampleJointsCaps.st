example
exampleJointsCaps
	"GeziraBindings exampleJointsCaps"
	| target vertices g |
	target := Form extent: 600@200 depth: 32.
	target fillWhite.
	vertices := #(0 0 0 0 30 -50  30 -50 30 -50 60 0).
	#(-1 0 1 15) withIndexDo: [:p :x |
		1 to: 30 by: 29 do: [:w |
			(g := GeziraBindings new)
				kernels: (
					g pipeline: {
						g funnel.
						g transformBeziers: (MatrixTransform2x3 withOffset: x@1 * 120).
						g strokeBezierPathW: w l: p c: (w = 1 ifTrue: [0] ifFalse: [p]).
						g clipBeziers: target boundingBox.
						g rasterize.
						g compositeUniformColorCA: 0.5 cR: 0 cG: 0 cB: 1 overImageARGB32: target});
				pour: vertices asFloatArray from: 1 to: vertices size final: true;
				sync]].
	Display getCanvas translucentImage: target at: 0@0
