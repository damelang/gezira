generated
kernelBilinearFilter: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result t |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #t type: 'nile_Process_t*'.
	argCount ~= 0
		ifTrue: [^self fail: 'wrong argument count in BilinearFilter'].
	t := self popKernel.
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to BilinearFilter'].
	result := self cCode: 'gezira_BilinearFilter(init, t)'.
	self pushKernel: result.
