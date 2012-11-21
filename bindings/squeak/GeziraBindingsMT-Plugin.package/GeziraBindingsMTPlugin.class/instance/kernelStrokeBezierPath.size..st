generated
kernelStrokeBezierPath: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result w l c |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #w type: 'float'.
	self var: #l type: 'float'.
	self var: #c type: 'float'.
	argCount ~= 3
		ifTrue: [^self fail: 'wrong argument count in StrokeBezierPath'].
	w := interpreterProxy floatValueOf: (argOops at: 0).
	l := interpreterProxy floatValueOf: (argOops at: 1).
	c := interpreterProxy floatValueOf: (argOops at: 2).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to StrokeBezierPath'].
	result := self cCode: 'gezira_StrokeBezierPath(init, w, l, c)'.
	self pushKernel: result.
