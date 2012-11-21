generating
generateBuilders
	"self generateBuilders"
	| firstArg type arg kernels params |
	self kernelDefinitionsDo: [:kernel :argDefs |
		self in: #GeziraBindings
			classified: 'building-generated'
			compile: (String streamContents: [:stream |
				stream nextPutAll: kernel withFirstCharacterDownshifted.
				firstArg := true.
				kernels := OrderedCollection new.
				params := OrderedCollection new.
				argDefs do: [:argDef |
					type := argDef first.
					arg := argDef second.
					firstArg ifTrue: [
						stream nextPutAll: arg capitalized, ': ', arg.
						firstArg := false.
					] ifFalse: [
						stream nextPutAll: ' ', arg, ': ', arg
					].
					type = 'Kernel'
						ifTrue: [kernels add: arg.
							stream nextPutAll: 'Kernel']
						ifFalse: [params add: arg]].
				stream crtab; nextPutAll: '"Automatically generated (see generateBuilders)"'.
				stream crtab; nextPutAll: '^ '.
				kernels do: [:k |
					stream nextPutAll: k; nextPutAll: 'Kernel, '].
				stream nextPutAll: '{{#Kernel. #', kernel.
				params do: [:p |
					stream nextPutAll: '. '; nextPutAll: p; nextPutAll: ' asFloat'].
				stream nextPutAll: '}}'.
				])]