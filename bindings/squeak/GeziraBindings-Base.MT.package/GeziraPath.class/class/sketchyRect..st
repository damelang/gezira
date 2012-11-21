instance creation
sketchyRect: aRectangle
	| ps origin corner p |
	origin := aRectangle origin.
	corner := aRectangle corner.
	p := 0.05.
	ps := Array streamContents: [:strm |
		strm nextPutAll: (self sketchyPointsFrom: origin to: (corner x@origin y) p: p).
		strm nextPutAll: (self sketchyPointsFrom: (corner x@origin y) to: corner p: p).
		strm nextPutAll: (self sketchyPointsFrom: corner to: (origin x@corner y) p: p).
		strm nextPutAll: (self sketchyPointsFrom: (origin x@corner y) to: origin p: p)].
	^ self new points: {ps}.
