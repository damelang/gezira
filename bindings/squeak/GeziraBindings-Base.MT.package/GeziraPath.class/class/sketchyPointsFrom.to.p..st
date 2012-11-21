private
sketchyPointsFrom: from to: to p: p
	| sequence midPoints points |
	sequence := self noiseSamplesFrom: from to: to p: p.
	sequence size = 0 ifTrue: [^ #()].
	midPoints := (1 to: sequence size - 1) collect: [:i |
		((sequence at: i) + (sequence at: i+1)) / 2.0].
	points := Array streamContents: [:strm |
		strm nextPut: (sequence at: 1);
				nextPut: (sequence at: 1);
				nextPut: (midPoints at: 1).
		2 to: sequence size - 1 do: [:i |
			strm
				nextPut: (midPoints at: i-1);
				nextPut: (sequence at: i);
				nextPut: (midPoints at: i)].
		strm
			nextPut: (midPoints last);
			nextPut: (midPoints last);
			nextPut: (sequence last)].
	^ points.

			
