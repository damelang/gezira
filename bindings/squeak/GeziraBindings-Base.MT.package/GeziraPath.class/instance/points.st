accessing
points
	^points ifNil: [
		points := {floats pairsCollect: [:x :y | x@y]}]