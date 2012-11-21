primitives
primExecuteThreads: nThreads memory: nBytes commands: pipelineSpec
	"This is the only primitive actually invoking Gezira - it executes an Array with commands"
	<primitive: 'primitiveExecuteThreadsMemCmds' module: 'GeziraBindingsMT'>
	^self pluginMissing ifFalse: [
		| item code message command |
		item := self primErrorItem.
		code := self primErrorCode.
		message := self primErrorMessage.
		command := (pipelineSpec at: item ifAbsent: [#(Unknown)]) first.
		command = #Kernel
			ifTrue: [command := (pipelineSpec at: item) second].
		self error: message, ' (', command, ': ', code asString, ')']