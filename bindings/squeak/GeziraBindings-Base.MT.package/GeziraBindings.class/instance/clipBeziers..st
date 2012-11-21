building
clipBeziers: aRectangle
	^self clipBeziersMinX: aRectangle left
		minY: aRectangle top
		maxX: aRectangle right
		maxY: aRectangle bottom
