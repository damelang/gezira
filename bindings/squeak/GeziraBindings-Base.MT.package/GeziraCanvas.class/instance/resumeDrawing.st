drawing
resumeDrawing
	(target isArray) ifTrue: [ target := target at: 1. ^true ].
	^false
