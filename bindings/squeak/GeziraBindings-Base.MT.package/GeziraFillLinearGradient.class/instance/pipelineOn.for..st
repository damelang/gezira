rendering
pipelineOn: g for: aCanvas
	from ifNil: [self fromTo].
	^g pipeline: {
		g transformPoints: aCanvas inverseTransformation.
		g linearGradientSX: from x sY: from y eX: to x eY: to y.
		g padGradient.
		g applyColorSpansSpans: (self stopsPipelineOn: g)}