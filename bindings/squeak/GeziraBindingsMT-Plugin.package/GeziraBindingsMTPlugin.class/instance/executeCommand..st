commands
executeCommand: commandArrayOop
	"Command is an Array like #('Cmd' arg1 arg2). Dispatch to the actual commands"

	| commandArray commandArraySize commandNameOop commandName commandNameSize |
	self returnTypeC: 'void'.
	self var: #commandName type: 'char*'.
	self var: #commandArray type: 'sqInt*'.

	commandArraySize := interpreterProxy slotSizeOf: commandArrayOop.
	commandArraySize > 0
		ifFalse: [^self fail: 'Empty command'].
	commandArray := interpreterProxy firstIndexableField: commandArrayOop.

	commandNameOop := interpreterProxy fetchPointer: 0 ofObject: commandArrayOop.
	(interpreterProxy isBytes: commandNameOop)
		ifFalse: [^self fail: 'Command name not a String'].
	commandName := interpreterProxy firstIndexableField: commandNameOop.
	commandNameSize := interpreterProxy slotSizeOf: commandNameOop.

	(self string: 'Kernel' equals: commandName len: commandNameSize)
		ifTrue: [^self executeKernel: commandArray+1 size: commandArraySize-1].
	(self string: 'Pour' equals: commandName len: commandNameSize)
		ifTrue: [^self executePour: commandArray+1 size: commandArraySize-1].
	(self string: 'Sync' equals: commandName len: commandNameSize)
		ifTrue: [^self executeSync: commandArray+1 size: commandArraySize-1].

	self fail: 'Unknown command'.
