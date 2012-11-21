building
sync
	"This concludes a rendering pipeline and starts the rendering, then clears the pipeline"
	commands ifNil: [^self].
	ShowPipeline == true ifTrue: [Transcript show: self commandsStringPrefix].
	"Transcript clear; show: self commandsStringC"
	false ifTrue: [
			FileStream newFileNamed: (FileDirectory default nextNameFor: self pluginName extension: 'txt')
			do: [:f | f nextPutAll: self commandsStringC]].
	[
	[self primExecuteThreads: self threads
		memory: self memory
		commands: commands
	] on: Error do: [:error |
		(error messageText beginsWith: 'Unknown kernel')
			ifTrue: [
				self beep.
				Transcript show: error messageText; space; show: (commands at: self primErrorItem) second; show: ' (EMULATING)'; cr.
				(self as: GZBindings) sync]
			ifFalse: [
				Transcript show: error messageText; show: ' (LOGGED)'; cr.
				FileStream newFileNamed: (FileDirectory default nextNameFor: self pluginName extension: 'txt')
					do: [:f | f nextPutAll: self commandsStringC].
				error pass]].
	] ensure: [commands := nil].
