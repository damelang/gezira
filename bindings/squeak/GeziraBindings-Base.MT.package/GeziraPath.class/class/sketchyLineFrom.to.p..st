instance creation
sketchyLineFrom: from to: to p: p
	^ self new points: {self sketchyPointsFrom: from to: to p: p}.
