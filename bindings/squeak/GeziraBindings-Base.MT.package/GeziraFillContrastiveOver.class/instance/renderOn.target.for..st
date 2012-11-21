rendering
renderOn: g target: targetForm for: aCanvas
	^{
		g rasterize.
		g applyTextureT: 
			(g pipeline: {
				g readFromImageARGB32: targetForm.
				g contrastiveOverA: amount}).
		g writeToImageARGB32: targetForm
	}
