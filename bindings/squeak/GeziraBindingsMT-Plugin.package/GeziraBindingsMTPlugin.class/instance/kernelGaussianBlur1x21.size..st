generated
kernelGaussianBlur1x21: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result f t |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #f type: 'float'.
	self var: #t type: 'nile_Process_t*'.
	argCount ~= 1
		ifTrue: [^self fail: 'wrong argument count in GaussianBlur1x21'].
	t := self popKernel.
	f := interpreterProxy floatValueOf: (argOops at: 0).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to GaussianBlur1x21'].
	result := self cCode: 'gezira_GaussianBlur1x21(init, f, t)'.
	self pushKernel: result.
