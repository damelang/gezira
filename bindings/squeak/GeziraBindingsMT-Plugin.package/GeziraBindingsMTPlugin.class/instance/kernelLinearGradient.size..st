generated
kernelLinearGradient: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result sX sY eX eY |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #sX type: 'float'.
	self var: #sY type: 'float'.
	self var: #eX type: 'float'.
	self var: #eY type: 'float'.
	argCount ~= 4
		ifTrue: [^self fail: 'wrong argument count in LinearGradient'].
	sX := interpreterProxy floatValueOf: (argOops at: 0).
	sY := interpreterProxy floatValueOf: (argOops at: 1).
	eX := interpreterProxy floatValueOf: (argOops at: 2).
	eY := interpreterProxy floatValueOf: (argOops at: 3).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to LinearGradient'].
	result := self cCode: 'gezira_LinearGradient(init, sX, sY, eX, eY)'.
	self pushKernel: result.
