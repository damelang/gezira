drawing
drawOn: aCanvas
	stroke ifNotNil: [aCanvas stroke: stroke]. 
	super drawOn: aCanvas