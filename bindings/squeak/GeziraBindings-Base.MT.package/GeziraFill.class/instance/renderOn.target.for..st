rendering
renderOn: g target: targetForm for: aCanvas
	^{
		g rasterize.
		g applyTextureT: (self isOpaque
			ifTrue: [self pipelineOn: g for: aCanvas]
			ifFalse: [
				g compositeTexturesT1: (self pipelineOn: g for: aCanvas)
					t2: (g readFromImageARGB32: targetForm)
					c: g compositeOver]).
		g writeToImageARGB32: targetForm
	}
