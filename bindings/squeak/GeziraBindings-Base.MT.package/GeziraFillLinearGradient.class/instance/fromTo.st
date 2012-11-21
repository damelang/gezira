accessing
fromTo
	| distanceFromOrigin gradientLength gradientVector |
	from ifNil: [
		"infer to/from based on deprecated delta/offset"
		gradientVector := delta * ((1.0 / delta r) raisedTo: 2).
		gradientLength := gradientVector r.
		distanceFromOrigin := offset * gradientLength negated.
		from := (gradientVector / gradientLength) * distanceFromOrigin.
		to := from + gradientVector.
		from := from roundTo: 0.000001@0.000001.
		to := to roundTo: 0.000001@0.000001].
	^ {from. to}