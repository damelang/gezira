mixing
maxRedStop
	"Return the redest of the stops.  If all have the same red, return the color red."
	
	| maxRed mrEntry |
	maxRed := stops inject: 0 into: [:red :assoc | 
			(assoc value at: 1) max: red].
	mrEntry := (stops detect: [:assoc | (assoc value at: 2) = maxRed] 
					ifNone: [^ Color red]) value.
	^ Color r: (mrEntry at: 1) g: (mrEntry at: 2) b: (mrEntry at: 3) 
					alpha: (mrEntry at: 4).
