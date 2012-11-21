converting
transformedBy: aTransform 
	| path |
	path := super transformedBy: aTransform.
	path fill: fill.
	^ path.
