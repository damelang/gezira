generated
kernelRectangleSpans: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result minX minY maxX maxY |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #minX type: 'float'.
	self var: #minY type: 'float'.
	self var: #maxX type: 'float'.
	self var: #maxY type: 'float'.
	argCount ~= 4
		ifTrue: [^self fail: 'wrong argument count in RectangleSpans'].
	minX := interpreterProxy floatValueOf: (argOops at: 0).
	minY := interpreterProxy floatValueOf: (argOops at: 1).
	maxX := interpreterProxy floatValueOf: (argOops at: 2).
	maxY := interpreterProxy floatValueOf: (argOops at: 3).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to RectangleSpans'].
	result := self cCode: 'gezira_RectangleSpans(init, minX, minY, maxX, maxY)'.
	self pushKernel: result.
