accessing
minMaxWithTransform: aTransform
	| p min max |
	min := max := nil.
	self floats pairsDo: [:x :y |
		p := aTransform transformPoint: x@y.
		min := min ifNil: [p] ifNotNil: [min min: p].
		max := max ifNil: [p] ifNotNil: [max max: p]].
	min ifNil: [min := 0.0@0.0].
	max ifNil: [max := 0.0@0.0].
	^min corner: max