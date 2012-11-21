drawing
drawOn: aCanvas
	fill ifNotNil: [aCanvas fill: fill].
	super	drawOn: aCanvas.