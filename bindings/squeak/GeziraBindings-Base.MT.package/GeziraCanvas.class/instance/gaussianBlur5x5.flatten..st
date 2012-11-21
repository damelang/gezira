effects
gaussianBlur5x5: aPath flatten: flattenFactor
	| tempForm g |
	"blur target horizontally to temp form, 	then blur temp form vertically back on target"
	tempForm := Form extent: target extent depth: 32.
	(g := GeziraBindings new)
		kernels: (
			g pipeline: {
				g funnel.
				g rectangleSpansMinX: 0 minY: 0 maxX: tempForm width maxY: tempForm height.
				g applyTextureT: (
					g gaussianBlur5x1F: flattenFactor t: (
						g readFromImageARGB32: target)).
				g writeToImageARGB32: tempForm});
		pour: FloatArray new; "trigger rectangleSpans"
		sync;	"finish writing to temp form"
		kernels: (
			g pipeline: {
				g funnel.
				g rectangleSpansMinX: 0 minY: 0 maxX: target width maxY: target height.
				g applyTextureT: (
					g gaussianBlur1x5F: flattenFactor t: (
						g readFromImageARGB32: tempForm)).
				g writeToImageARGB32: target});
		pour: FloatArray new; "trigger rectangleSpans"
		sync.