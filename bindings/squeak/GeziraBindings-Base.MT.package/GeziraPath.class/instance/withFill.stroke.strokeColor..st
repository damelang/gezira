converting
withFill: fillColor stroke: stroke strokeColor: strokeColor 
	"Return a collection of GeziraFillPath or
	GeziraStrokePath that have given color and border"
	| paths |
	paths := OrderedCollection new.
	fillColor isTransparent
		ifFalse: [paths
				add: ((GeziraFilledPath path: self) withClosedContours fill: fillColor)].
	stroke
		ifNotNil: [(stroke width > 0
					and: [strokeColor isTransparent not])
				ifTrue: [paths add: ((GeziraStrokedPath path: self) fill: strokeColor;
							 stroke: stroke)]].
	^ paths