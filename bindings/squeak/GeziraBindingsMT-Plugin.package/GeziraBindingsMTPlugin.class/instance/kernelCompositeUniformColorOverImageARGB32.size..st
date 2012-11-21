commands
kernelCompositeUniformColorOverImageARGB32: argOops size: argCount
	"Argument is a Form and 4 Floats for the color"
	| result alpha red green blue image |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #image type: 'gezira_Image_t*'.
	self var: #alpha type: 'float'.
	self var: #red type: 'float'.
	self var: #green type: 'float'.
	self var: #blue type: 'float'.

	argCount ~= 5
		ifTrue: [^self fail: 'wrong kernel argument count in WriteToImageARGB32UniformColor'].

	alpha := interpreterProxy floatValueOf: (argOops at: 0).
	red := interpreterProxy floatValueOf: (argOops at: 1).
	green := interpreterProxy floatValueOf: (argOops at: 2).
	blue := interpreterProxy floatValueOf: (argOops at: 3).
	interpreterProxy failed ifTrue: [^self fail: 'invalid color components in WriteToImageARGB32UniformColor'].

	image := self imageFromForm: (argOops at: 4).
	interpreterProxy failed ifTrue: [^nil].

	result := self cCode: 'gezira_CompositeUniformColorOverImage_ARGB32 (init, image, alpha, red, green, blue)'
		inSmalltalk: [alpha. red. green. blue. image].
	self pushKernel: result.
