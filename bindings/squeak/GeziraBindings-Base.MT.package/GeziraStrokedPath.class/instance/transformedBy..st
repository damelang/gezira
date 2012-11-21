converting
transformedBy: aTransform 
	| path |
	path := super transformedBy: aTransform.
	path stroke: stroke.
	^ path.
