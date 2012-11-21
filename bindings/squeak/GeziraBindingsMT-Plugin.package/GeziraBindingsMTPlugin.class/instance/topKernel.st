misc
topKernel
	self returnTypeC: #'nile_Process_t*'.
	stackP < 1
		ifTrue: [self fail: 'empty stack'. ^nil].
	^stack at: stackP - 1