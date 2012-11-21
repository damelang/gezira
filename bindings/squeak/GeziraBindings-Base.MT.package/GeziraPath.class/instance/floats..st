accessing
floats: anArray
	floats := anArray asFloatArray.
	floats size \\ 6 = 0 ifFalse: [self error: 'invalid path'].
	points := nil.
