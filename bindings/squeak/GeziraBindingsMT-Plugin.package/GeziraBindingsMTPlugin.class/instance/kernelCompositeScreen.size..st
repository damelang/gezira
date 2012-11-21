generated
kernelCompositeScreen: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	argCount ~= 0
		ifTrue: [^self fail: 'wrong argument count in CompositeScreen'].
	result := self cCode: 'gezira_CompositeScreen(init)'.
	self pushKernel: result.
