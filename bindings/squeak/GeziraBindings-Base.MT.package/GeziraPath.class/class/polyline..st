instance creation
polyline: aPointArray
	^self new points: {
		Array streamContents: [:stream |
			1 to: aPointArray size - 1 do: [:i | | p1 p2 |
				p1 := aPointArray at: i.
				p2 := aPointArray at: i + 1.
				stream nextPut: p1; nextPut: p2; nextPut: p2]]}