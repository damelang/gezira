printing
commandsStringPrefix
	"Return pipeline print string in prefix notation (that is, like nested function calls)."
	| specs stack kernel realArgs kernelArgs func crtab crbartab |
	specs := self commandsSpecs.
	crtab := String cr, String tab.
	crbartab := String cr, '|', String tab.
	stack := OrderedCollection new.
	commands do: [:cmd |
		cmd first caseOf: {
			[#Kernel] -> [
				kernel := cmd second.
				realArgs := cmd allButFirst: 2.
				kernelArgs := stack removeLast: (kernel = #Pipeline
					ifTrue: [cmd third]
					ifFalse: [(specs at: kernel) count: [:s | s first = #Kernel]]).
				func := String streamContents: [:stream |
					stream nextPutAll: kernel, '('.
					realArgs do: [:a | stream space; print: (a isFloat ifTrue: [a roundTo: 0.001] ifFalse: [a])].
					kernelArgs withIndexDo: [:a :i |
						stream cr; nextPutAll: (i < kernelArgs size ifTrue: ['|--'] ifFalse: ['\--']);
							nextPutAll: (a copyReplaceAll: String cr
								with: (i < kernelArgs size ifTrue: [crbartab] ifFalse: [crtab]))].
					stream nextPutAll: ' )'].
				stack addLast: func].
			[#Pour] -> [stack add: (String streamContents: [:stream |
				stream nextPutAll: 'Pour([ '.
				cmd second do: [:v | stream print: (v roundTo: 0.001); space].
				stream nextPutAll: '] '.
				(cmd allButFirst: 2) do: [:a | stream print: a; space].
				stream nextPutAll: ')'.
				])].
			[#Sync] -> [stack add: 'Sync()'].
		}].
	^String streamContents: [:s |
		stack do: [:c | s nextPutAll: c asString; cr]]