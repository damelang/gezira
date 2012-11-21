instance creation
gradient: anArray from: startPoint to: endPoint
	^GeziraFillLinearGradient new
		from: startPoint to: endPoint;
		stops: anArray