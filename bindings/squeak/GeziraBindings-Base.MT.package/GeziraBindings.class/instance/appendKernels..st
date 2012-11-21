accessing
appendKernels: anArray
	commands
		ifNil: [commands := anArray]
		ifNotNil: [commands := commands , anArray].
