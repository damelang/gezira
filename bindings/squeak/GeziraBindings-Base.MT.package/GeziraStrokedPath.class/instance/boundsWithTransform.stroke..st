accessing
boundsWithTransform: transform stroke: aStroke
	^super boundsWithTransform: transform
		stroke: (stroke ifNotNil: [stroke] ifNil: [aStroke])