primitives
primitiveExecuteThreads: newThreads memory: newMemSize commands: allCommandsOop
	"argument is an array of commands like #(#(Cmd1 args) #(Cmd2 args))"
	| allCommands allCommandsSize eachCommandOop |
	self primitive: 'primitiveExecuteThreadsMemCmds' parameters: #(SmallInteger SmallInteger Oop).
	self var: #allCommands type: 'sqInt*'.
	(interpreterProxy isArray: allCommandsOop)
		ifFalse: [self fail: 'argument must be an Array'. ^nil].
	(newMemSize > 0 and: [newThreads > 0])
		ifFalse: [self fail: 'need memory and threads'. ^ nil].

	newMemSize ~= memSize ifTrue: [
		mem notNil ifTrue: [
			self cCode: 'free (nile_shutdown (init))'].
		threads := 0.
		memSize := newMemSize.
		mem := self malloc: memSize.
		mem isNil ifTrue: [self fail: 'buffer allocation failed'. ^nil].
	].
	threads ~= newThreads ifTrue: [
		threads ~= 0 ifTrue: [self cCode: 'nile_shutdown (init)'].
		threads := newThreads.
		init := self cCode: 'nile_startup (mem, memSize, threads)'.
		init isNil ifTrue: [
			threads := 0.
			self fail: 'nile_startup failed'. ^nil]].

	self reset.

	allCommands := interpreterProxy firstIndexableField: allCommandsOop.
	allCommandsSize := interpreterProxy slotSizeOf: allCommandsOop.
	0 to: allCommandsSize - 1 do: [:i |
		errorItem := i + 1.
		eachCommandOop := allCommands at: i.
		(interpreterProxy isArray: eachCommandOop)
			ifFalse: [self fail: 'Command must be an Array'. ^nil].
		wasSync := false.
		self executeCommand: eachCommandOop.
		interpreterProxy failed
			ifTrue: [^nil].
		self checkNileError.
		interpreterProxy failed
			ifTrue: [^nil]].

	wasSync ifFalse: [
		errorItem := errorItem + 1.
		self executeSync: nil size: 0]
