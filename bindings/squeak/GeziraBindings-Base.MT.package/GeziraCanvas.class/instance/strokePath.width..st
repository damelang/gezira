old protocol
strokePath: aPath width: aWidth
	stroke := GeziraStroke width: aWidth.
	self drawPath: aPath.
	stroke := nil.