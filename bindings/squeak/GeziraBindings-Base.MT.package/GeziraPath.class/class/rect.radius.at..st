instance creation
rect: rect radius: radius at: whichCorners
	"whichCorners is an array of symbols specifying which corners to round (that is, any combination of #all, #bottom, #bottomLeft, #bottomRight, #left, #right, #top, #topLeft, #topRight)"

	^self rect: rect radii: (#(
		(left top topLeft all)
		(left bottom bottomLeft all)
		(right bottom bottomRight all)
		(right top topRight all)) collect: [:corners |
			((corners includes: whichCorners) or: [corners includesAnyOf: whichCorners])
				ifTrue: [radius]
				ifFalse: [0]])
