matrix primitives
primitiveTransformPoint: aPoint
	| matrix |
	self inline: false.
	self primitive: 'primitiveTransformPoint' parameters: #(Oop).
	self var: #matrix type:'float *'.
	self loadArgumentPoint: aPoint.
	matrix := self loadArgumentMatrix: (interpreterProxy stackObjectValue: 1).
	interpreterProxy failed ifTrue:[^nil].
	self matrix2x3TransformPoint: matrix.
	^ self makePoint: m23ResultX and: m23ResultY.
