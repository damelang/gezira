accessing
stops: aCollection
	stops := SortedCollection new.
	aCollection do: [:each | self addStop: each value at: each key].