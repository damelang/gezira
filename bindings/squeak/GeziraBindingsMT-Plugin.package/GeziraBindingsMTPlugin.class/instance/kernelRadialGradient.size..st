generated
kernelRadialGradient: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result cX cY r |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #cX type: 'float'.
	self var: #cY type: 'float'.
	self var: #r type: 'float'.
	argCount ~= 3
		ifTrue: [^self fail: 'wrong argument count in RadialGradient'].
	cX := interpreterProxy floatValueOf: (argOops at: 0).
	cY := interpreterProxy floatValueOf: (argOops at: 1).
	r := interpreterProxy floatValueOf: (argOops at: 2).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to RadialGradient'].
	result := self cCode: 'gezira_RadialGradient(init, cX, cY, r)'.
	self pushKernel: result.
