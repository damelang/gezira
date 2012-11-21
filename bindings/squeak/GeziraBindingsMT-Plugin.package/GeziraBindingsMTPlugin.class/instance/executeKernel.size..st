commands
executeKernel: argOops size: argCount
	"A kernel command looks like #('KernelName' arg1 arg2). Dispatch on the name."

	| kernelNameOop kernelName kernelNameSize |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #kernelName type: 'char*'.

	argCount < 1
		ifTrue: [^self fail: 'No kernel name given'].

	kernelNameOop := argOops at: 0.
	(interpreterProxy isBytes: kernelNameOop)
		ifFalse: [^self fail: 'kernel name not a String'].
	kernelName := interpreterProxy firstIndexableField: kernelNameOop.
	kernelNameSize := interpreterProxy slotSizeOf: kernelNameOop.

	self dispatchKernel: kernelName size: kernelNameSize arguments: argOops + 1 size: argCount - 1.