accessing
floats
	^floats ifNil: [
		floats := FloatArray streamContents: [:path |
			points do: [:contour |
				contour size \\ 3 = 0 ifFalse: [self error: 'invalid path'].
				contour do: [:p |
					path nextPut: p x; nextPut: p y]]]]