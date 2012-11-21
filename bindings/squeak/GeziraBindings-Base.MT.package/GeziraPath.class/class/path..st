instance creation
path: aPath
	self class == aPath class
		ifTrue: [^aPath].
	^self new, aPath asGeziraPath