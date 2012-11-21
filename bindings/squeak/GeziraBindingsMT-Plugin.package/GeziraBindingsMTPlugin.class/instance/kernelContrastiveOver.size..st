generated
kernelContrastiveOver: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result a |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #a type: 'float'.
	argCount ~= 1
		ifTrue: [^self fail: 'wrong argument count in ContrastiveOver'].
	a := interpreterProxy floatValueOf: (argOops at: 0).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to ContrastiveOver'].
	result := self cCode: 'gezira_ContrastiveOver(init, a)'.
	self pushKernel: result.
