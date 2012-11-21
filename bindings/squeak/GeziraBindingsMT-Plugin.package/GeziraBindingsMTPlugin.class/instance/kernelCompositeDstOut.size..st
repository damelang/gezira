generated
kernelCompositeDstOut: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	argCount ~= 0
		ifTrue: [^self fail: 'wrong argument count in CompositeDstOut'].
	result := self cCode: 'gezira_CompositeDstOut(init)'.
	self pushKernel: result.
