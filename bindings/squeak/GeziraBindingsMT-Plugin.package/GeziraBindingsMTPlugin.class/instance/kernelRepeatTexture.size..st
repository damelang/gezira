generated
kernelRepeatTexture: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result dX dY |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #dX type: 'float'.
	self var: #dY type: 'float'.
	argCount ~= 2
		ifTrue: [^self fail: 'wrong argument count in RepeatTexture'].
	dX := interpreterProxy floatValueOf: (argOops at: 0).
	dY := interpreterProxy floatValueOf: (argOops at: 1).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to RepeatTexture'].
	result := self cCode: 'gezira_RepeatTexture(init, dX, dY)'.
	self pushKernel: result.
