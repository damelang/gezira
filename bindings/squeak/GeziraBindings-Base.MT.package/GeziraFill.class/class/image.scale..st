instance creation
image: aForm scale: aNumber
	^ (self image: aForm)
		transform: (MatrixTransform2x3 withScale: aNumber)