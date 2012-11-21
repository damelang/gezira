transforming
translateBy: offset
	^self transformBy: (MatrixTransform2x3 withOffset: offset)