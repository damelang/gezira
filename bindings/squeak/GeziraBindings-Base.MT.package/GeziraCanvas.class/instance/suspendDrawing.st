drawing
suspendDrawing
	(target isArray) ifFalse: [ target := Array with: target. ^true ].
	^false
