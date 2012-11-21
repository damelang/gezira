converting
asClosedPath
	"Add a line segment from last to first point if they are not identical. This is only correct if this path has a single contour. For multiple contours, use the more expensive #withClosedContours."
	| s x0 y0 x1 y1 |
	s := self floats size.
	s = 0 ifTrue: [^self].
	x0 := floats at: 1.
	y0 := floats at: 2.
	x1 := floats at: s-1.
	y1 := floats at: s.
	^ (x0 = x1 and: [y0 = y1])
		ifTrue: [self]
		ifFalse: [self clone
			floats: (self floats, {x1. y1. x1. y1. x0. y0})].
