mixing
mixed: proportion with: other
	| frac1 frac2 |
	other class == self class
		ifFalse: [^super mixed: proportion with: other].
	frac1 := proportion asFloat min: 1.0 max: 0.0.
	frac2 := 1.0 - frac1.
	^ self class new
		setAlpha: alpha * frac1 + (other alpha * frac2)
		red: red * frac1 + (other red * frac2)
		green: green * frac1 + (other green * frac2)
		blue: blue * frac1 + (other blue * frac2)