accessing
containsPoint: aPoint withTransform: aTransform stroke: aStroke
	^super containsPoint: aPoint
		withTransform: aTransform
		stroke: (stroke ifNotNil: [stroke] ifNil: [aStroke])