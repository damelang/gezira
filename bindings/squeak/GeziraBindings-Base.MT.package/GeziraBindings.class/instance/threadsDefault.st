accessing
threadsDefault
	^Threads ifNil: [self class optimizeNumberOfThreads]
