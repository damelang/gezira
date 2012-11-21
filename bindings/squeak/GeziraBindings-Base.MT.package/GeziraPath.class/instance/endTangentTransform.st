accessing
endTangentTransform
	"Return a transform which rotates along the end tangent and move to the end."
	| triplet direction |
	triplet := self points first last: 3.
	direction := (triplet third = triplet first
		ifTrue: [1@0]
		ifFalse: [triplet third - triplet first]) normalized.

	^ MatrixTransform2x3 new
		a11: direction x; a12: direction y negated; a13: triplet last x;
		a21: direction y; a22: direction x;         a23: triplet last y.