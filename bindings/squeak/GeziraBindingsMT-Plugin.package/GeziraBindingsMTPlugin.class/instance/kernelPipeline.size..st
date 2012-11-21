commands
kernelPipeline: argOops size: argCount
	"Argument is an integer, pops n kernels"
	| result n v |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #v type: 'nile_Process_t**'.

	argCount ~= 1
		ifTrue: [^self fail: 'wrong kernel argument count in Pipeline'].

	n := interpreterProxy checkedIntegerValueOf: (argOops at: 0).
	v := self popKernels: n.
	interpreterProxy failed ifTrue: [^nil].

	result := self cCode: 'nile_Process_pipe_v (v, n)' inSmalltalk: [v. n].
	self pushKernel: result.
