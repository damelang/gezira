accessing
startTangentTransform
	"Return a transform which rotates along the start tangent and move to the start."
	| triplet direction p |
	triplet := self points first first: 3.
	p := triplet first = triplet second
		ifTrue: [triplet third]
		ifFalse: [triplet second].
	direction := (triplet first = p
		ifTrue: [1@0]
		ifFalse: [triplet first - p]) normalized.
	^ MatrixTransform2x3 new
		a11: direction x; a12: direction y negated; a13: triplet first x;
		a21: direction y; a22: direction x;         a23: triplet first y.