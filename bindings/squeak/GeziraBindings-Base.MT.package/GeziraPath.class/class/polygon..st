instance creation
polygon: aPointArray
	^self new points: {
		Array streamContents: [:stream |
			aPointArray withIndexDo: [:p1 :i | | p2 |
				p2 := aPointArray atWrap: i + 1.
				stream nextPut: p1; nextPut: p2; nextPut: p2]]}