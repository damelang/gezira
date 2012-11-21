misc
popKernel
	self returnTypeC: #'nile_Process_t*'.
	stackP > 0
		ifFalse: [self fail: 'kernel stack underflow'. ^nil].
	stackP := stackP - 1.
	^stack at: stackP