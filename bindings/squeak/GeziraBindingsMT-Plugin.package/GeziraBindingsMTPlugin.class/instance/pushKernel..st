misc
pushKernel: aKernel
	self inline: true.
	self returnTypeC: 'void'.
	self var: #aKernel type: #'nile_Process_t*'.
	stackP < (stack sizeof / (stack at: 0) sizeof)
		ifFalse: [self fail: 'kernel stack overflow'. ^nil].
	stack at: stackP put: aKernel.
	stackP := stackP + 1.
