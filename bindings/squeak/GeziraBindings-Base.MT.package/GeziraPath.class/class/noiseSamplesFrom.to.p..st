private
noiseSamplesFrom: from to: to p: p
	| rand unit unitP unitMag |
	rand := Random new.
	unit := to - from.
	unitMag := unit r.
	unitMag <= 1.0 ifTrue: [^ #()].
	unitP := (unit y@unit x negated) * p / (unitMag log: 8).
	^ (0.0 to: 1.0 by: 0.125) collect: [:f |
		from + (unit * f) + (((f = 0.0 or: [f = 1.0]) ifTrue: [0.0] ifFalse: [rand next - 0.5]) * unitP)].
