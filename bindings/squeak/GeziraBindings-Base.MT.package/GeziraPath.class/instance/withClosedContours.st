converting
withClosedContours
	"Close each of the contours in this path with a line segment"
	| thisA thisC prevC firstInContour contourStart newFloats |
	thisC := nil.
	newFloats := nil.
	1 to: self floats size by: 6 do: [:i |
		prevC := thisC.
		thisA := (floats at: i)@(floats at: i+1).
		thisC := (floats at: i+4)@(floats at: i+5).
		i = 1 ifTrue: [
			firstInContour := thisA.
			contourStart := i].
		(prevC notNil and: [prevC ~= thisA]) ifTrue: [
			"contour ended"
			firstInContour = prevC ifFalse: [
				"not closed"
				newFloats ifNil: [newFloats := floats copyFrom: 1 to: contourStart - 1].
				newFloats := newFloats, (floats copyFrom: contourStart to: i - 1),
					{prevC x. prevC y. prevC x. prevC y. firstInContour x. firstInContour y}.
			].
			firstInContour := thisA.
			contourStart := i.
		].
	].
	firstInContour = thisC ifFalse: [
		"not closed"
		newFloats ifNil: [newFloats := floats copyFrom: 1 to: contourStart - 1].
		newFloats := newFloats, (floats copyFrom: contourStart to: floats size),
		{thisC x. thisC y. thisC x. thisC y. firstInContour x. firstInContour y}].
	^newFloats
		ifNil: [self]
		ifNotNil:[self clone floats: newFloats]