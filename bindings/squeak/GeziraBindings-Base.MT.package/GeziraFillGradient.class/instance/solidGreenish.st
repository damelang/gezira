mixing
solidGreenish
	"Return a color for button rollover that is the greenest of the stops.  If all have the same green, return the solid green."
	
	| maxGreen |
	^ (maxGreen := self maxGreenStop) ~= self maxRedStop
		ifTrue: [maxGreen]
		ifFalse: [Color green]