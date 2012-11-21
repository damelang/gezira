mixing
maxGreenStop
	"Return the greenest of the stops.  If all have the same green, return the color green."
	
	| maxGreen mgEntry |
	maxGreen := stops inject: 0 into: [:green :assoc | 
			(assoc value at: 2) max: green].
	mgEntry := (stops detect: [:assoc | (assoc value at: 2) = maxGreen] 
					ifNone: [ ^ Color green]) value.
	^ Color r: (mgEntry at: 1) g: (mgEntry at: 2) b: (mgEntry at: 3) 
					alpha: (mgEntry at: 4).
