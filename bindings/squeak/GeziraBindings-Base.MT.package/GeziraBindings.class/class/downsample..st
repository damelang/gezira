utilities
downsample: aForm
	"return a form half the size of aForm"
	| target vertices g t |
	aForm extent <= (1@1) ifTrue: [^aForm].
	target := Form extent: aForm extent // 2 depth: 32.
	t := MatrixTransform2x3 withScale: aForm extent / target extent.
	vertices := (0@0 extent: target extent) asGeziraPath.
	(g := self new)
		kernels: (
			g pipeline: {
				g funnel.
				g rasterize.
				g applyTextureT: (
					g pipeline: {
						g transformPoints: t.
						g bilinearFilterT: (
							g readFromImageARGB32: aForm)}).
				g writeToImageARGB32: target});
		pour: vertices from: 1 to: vertices size final: true;
		sync.
	^target