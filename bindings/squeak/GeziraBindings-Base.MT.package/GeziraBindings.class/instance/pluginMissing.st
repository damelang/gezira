primitives
pluginMissing
	| moduleName |
	moduleName := thisContext sender method literals first first.
	(Smalltalk listLoadedModules noneSatisfy: [:each | each beginsWith: moduleName])
		ifTrue: [
			Smalltalk unloadModule: moduleName.
			self error: moduleName, ' plugin not found'.
			^true].
	^false