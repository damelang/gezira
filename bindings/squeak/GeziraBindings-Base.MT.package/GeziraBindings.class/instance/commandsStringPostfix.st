printing
commandsStringPostfix
	"Return pipeline print string in postfix notation (that is, as stack construction calls)"
	| specs stack kernel realArgs kernelArgs func lines |
	specs := self commandsSpecs.
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
					kernelArgs withIndexDo: [:a :ai |
						lines := a findTokens: Character cr.
						lines withIndexDo: [:l :li |
							stream nextPutAll: (li < lines size
									ifTrue: [ai = 1 ifTrue: ['	'] ifFalse: ['|	']]
									ifFalse: [ai = 1 ifTrue: ['/--'] ifFalse: ['|--']]);
								nextPutAll: l; cr]].
					stream nextPutAll: kernel, '('.
					realArgs do: [:a | stream space; print: (a isFloat ifTrue: [a roundTo: 0.001] ifFalse: [a])].
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