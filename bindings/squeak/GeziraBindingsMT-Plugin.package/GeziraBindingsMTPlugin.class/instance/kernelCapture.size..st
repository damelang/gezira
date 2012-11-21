commands
kernelCapture: argOops size: argCount
	"Argument is a FloatArray"
	| arrayOop array n arraySize result |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #array type: 'float*'.
	self var: #n type: 'static int'.

	argCount ~= 1
		ifTrue: [^self fail: 'wrong kernel argument count in Capture'].

	arrayOop := argOops at: 0.

	array := interpreterProxy arrayValueOf:  arrayOop.
	interpreterProxy failed ifTrue: [^self fail: 'invalid array'].
	arraySize := interpreterProxy slotSizeOf: arrayOop.
	n := 0.
	result := self cCode: 'nile_Capture (init, array, &n, arraySize)'
		inSmalltalk: [array. arraySize. n].
	self pushKernel: result.
