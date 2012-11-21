generated
kernelTransformBeziers: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result mA mB mC mD mE mF |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #mA type: 'float'.
	self var: #mB type: 'float'.
	self var: #mC type: 'float'.
	self var: #mD type: 'float'.
	self var: #mE type: 'float'.
	self var: #mF type: 'float'.
	argCount ~= 6
		ifTrue: [^self fail: 'wrong argument count in TransformBeziers'].
	mA := interpreterProxy floatValueOf: (argOops at: 0).
	mB := interpreterProxy floatValueOf: (argOops at: 1).
	mC := interpreterProxy floatValueOf: (argOops at: 2).
	mD := interpreterProxy floatValueOf: (argOops at: 3).
	mE := interpreterProxy floatValueOf: (argOops at: 4).
	mF := interpreterProxy floatValueOf: (argOops at: 5).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to TransformBeziers'].
	result := self cCode: 'gezira_TransformBeziers(init, mA, mB, mC, mD, mE, mF)'.
	self pushKernel: result.
