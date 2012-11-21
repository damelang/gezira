commands
kernelReadFromImageARGB32: argOops size: argCount
	"Argument is a Form"
	| result image |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #image type: 'gezira_Image_t*'.

	argCount ~= 1
		ifTrue: [^self fail: 'wrong kernel argument count in ReadFromImageARGB32'].

	image := self imageFromForm: (argOops at: 0).
	interpreterProxy failed ifTrue: [^nil].

	result := self cCode: 'gezira_ReadFromImage_ARGB32 (init, image, 1)'
		inSmalltalk: [image].
	self pushKernel: result.
