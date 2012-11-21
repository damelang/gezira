accessing
transformedExtent
	^transform
		ifNil: [form extent]
		ifNotNil: [form extent / (transform transformDirection: 1@1)]