converting
, aPath
	self floats: ((floats isNil and: [points isNil])
		ifTrue: [aPath asGeziraPath floats]
		ifFalse: [self floats, aPath asGeziraPath floats])
