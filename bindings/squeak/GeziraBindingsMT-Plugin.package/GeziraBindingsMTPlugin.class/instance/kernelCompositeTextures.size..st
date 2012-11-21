generated
kernelCompositeTextures: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result t1 t2 c |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #t1 type: 'nile_Process_t*'.
	self var: #t2 type: 'nile_Process_t*'.
	self var: #c type: 'nile_Process_t*'.
	argCount ~= 0
		ifTrue: [^self fail: 'wrong argument count in CompositeTextures'].
	c := self popKernel.
	t2 := self popKernel.
	t1 := self popKernel.
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to CompositeTextures'].
	result := self cCode: 'gezira_CompositeTextures(init, t1, t2, c)'.
	self pushKernel: result.
