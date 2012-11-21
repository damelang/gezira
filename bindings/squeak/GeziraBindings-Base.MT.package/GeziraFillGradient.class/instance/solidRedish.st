mixing
solidRedish
	"Return a color for button rollover that is the redest of the stops.  If all have the same red, return the solid red."
	
	| maxRed |
	^ (maxRed := self maxRedStop) ~= self maxGreenStop
		ifTrue: [maxRed]
		ifFalse: [Color red]