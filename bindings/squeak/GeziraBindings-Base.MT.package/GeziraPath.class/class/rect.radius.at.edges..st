instance creation
rect: rect radius: radius at: whichCorners edges: whichEdges
	"whichCorners is an array of symbols specifying which corners to round (that is, any combination of #all, #bottom, #bottomLeft, #bottomRight, #left, #right, #top, #topLeft, #topRight)"
	"whichEdges is an array of symbols specifying which edges to have (that is, any combination of #all, #bottom, #left, #right, #top)."

	^self rect: rect radii: (#(
		(left top topLeft all)
		(left bottom bottomLeft all)
		(right bottom bottomRight all)
		(right top topRight all)) collect: [:corners |
			((corners includes: whichCorners) or: [corners includesAnyOf: whichCorners])
				ifTrue: [radius]
				ifFalse: [0]])
		edges: (#((top all) (right all) (bottom all) (left all)) collect: [:edges |
			((edges includes: whichEdges) or: [edges includesAnyOf: whichEdges])])
