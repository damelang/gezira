generated
kernelUniformColor: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result cA cR cG cB |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #cA type: 'float'.
	self var: #cR type: 'float'.
	self var: #cG type: 'float'.
	self var: #cB type: 'float'.
	argCount ~= 4
		ifTrue: [^self fail: 'wrong argument count in UniformColor'].
	cA := interpreterProxy floatValueOf: (argOops at: 0).
	cR := interpreterProxy floatValueOf: (argOops at: 1).
	cG := interpreterProxy floatValueOf: (argOops at: 2).
	cB := interpreterProxy floatValueOf: (argOops at: 3).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to UniformColor'].
	result := self cCode: 'gezira_UniformColor(init, cA, cR, cG, cB)'.
	self pushKernel: result.
