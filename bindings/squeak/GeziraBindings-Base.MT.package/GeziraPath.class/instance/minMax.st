accessing
minMax
	| p min max |
	min := max := nil.
	self floats pairsDo: [:x :y |
		p := x@y.
		min := min ifNil: [p] ifNotNil: [min min: p].
		max := max ifNil: [p] ifNotNil: [max max: p]].
	^min corner: max