testing
isRectangularSeriesFrom: index equalsTo: v

	floats size = 24 ifFalse: [^ false].
	0 to: 10 do: [:i |
		(floats atWrap: (index + i)) = v ifFalse: [^ false]].
	^ true
