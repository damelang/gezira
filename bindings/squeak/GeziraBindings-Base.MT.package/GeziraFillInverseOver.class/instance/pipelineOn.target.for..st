rendering
pipelineOn: g target: targetForm for: aCanvas
	^g pipeline: {
		g readFromImageARGB32: targetForm.
		g inverseOverA: fraction}