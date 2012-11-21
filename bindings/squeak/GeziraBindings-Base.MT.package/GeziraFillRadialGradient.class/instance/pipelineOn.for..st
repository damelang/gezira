rendering
pipelineOn: g for: aCanvas
	^g pipeline: {
		g transformPoints: aCanvas inverseTransformation.
		g radialGradientCX: center x cY: center y r: radius.
		g padGradient.
		g applyColorSpansSpans: (self stopsPipelineOn: g)}