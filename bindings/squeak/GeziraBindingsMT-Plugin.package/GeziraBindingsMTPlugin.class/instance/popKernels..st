misc
popKernels: n
	self returnTypeC: #'nile_Process_t**'.
	stackP >= n
		ifFalse: [self fail: 'kernel stack underflow'. ^nil].
	stackP := stackP - n.
	^stack + stackP