example
exampleGradientRadial
	"GeziraBindings exampleGradientRadial"
	| target vertices m i g |
	target := Form extent: 400@300 depth: 32.
	vertices := GeziraCanvas star.
	m := MatrixTransform2x3 withOffset: 150@150.
 	i := m inverseTransformation.
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g transformBeziers: m.
				g clipBeziers: target boundingBox.
				g rasterize.
				g applyTextureT:
					(g pipeline: {
						g transformPoints: i.
						g radialGradientCX: 0.0 cY: 0.0 r: 100.0.
						g padGradient.
						g applyColorSpansSpans:
							(g pipeline: {
								g colorSpanS1A: 1.0 s1R: 1.0 s1G: 0.0 s1B: 0.0
									s2A: 1.0 s2R: 1.0 s2G: 1.0 s2B: 0.0
									l: 0.5. "red->yellow, length 0.5"
								g colorSpanS1A: 1.0 s1R: 1.0 s1G: 1.0 s1B: 0.0
									s2A: 1.0 s2R: 0.0 s2G: 1.0 s2B: 0.0
									l: 0.5. "yellow->green, length 0.5"})}).
				g writeToImageARGB32: target});
		pour: vertices from: 1 to: vertices size final: true;
		sync.
	Display getCanvas translucentImage: target at: 0@0
