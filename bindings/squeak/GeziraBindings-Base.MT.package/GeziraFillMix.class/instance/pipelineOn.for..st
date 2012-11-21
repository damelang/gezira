rendering
pipelineOn: g for: aCanvas
	^g compositeTexturesT1: (first pipelineOn: g for: aCanvas)
		t2: (second pipelineOn: g for: aCanvas)
		c: g compositeOver
