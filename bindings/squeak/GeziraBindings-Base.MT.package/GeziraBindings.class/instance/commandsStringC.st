printing
commandsStringC
	"Return pipeline print string in C notation (for reproducing bugs)"
	| specs stack kernel realArgs kernelArgs func crtab |
	specs := self commandsSpecs.
	crtab := String cr, String tab.
	stack := OrderedCollection new.
	commands do: [:cmd |
		cmd first caseOf: {
			[#Kernel] -> [
				kernel := cmd second.
				realArgs := cmd allButFirst: 2.
				kernelArgs := stack removeLast: (kernel = #Pipeline
					ifTrue: [realArgs := #(). cmd third]
					ifFalse: [(specs at: kernel) count: [:s | s first = #Kernel]]).
				func := String streamContents: [:stream |
					stream nextPutAll: 'gezira_', kernel, '(init'.
					realArgs do: [:a | stream nextPutAll: ', '; print: a].
					kernelArgs withIndexDo: [:a :i |
						stream nextPutAll: ', '; crtab; nextPutAll: (a copyReplaceAll: String cr with: crtab)].
					stream nextPutAll: ')'].
				stack addLast: func].
			[#Pour] -> [stack add: (String streamContents: [:stream |
				stream nextPutAll: 'nile_Funnel_pour(pipe, {'.
				cmd second do: [:v | stream print: v] separatedBy: [stream nextPutAll: ', '].
				stream nextPutAll: '}, '; print: cmd third - 1.
				(cmd allButFirst: 3) do: [:a | stream nextPutAll: ', '; print: a].
				stream nextPutAll: ')'.
				])].
			[#Sync] -> [stack add: 'Sync()'].
		}].
	^String streamContents: [:s |
		s nextPutAll: 'pipe = '.
		stack do: [:c | s nextPutAll: c asString; cr]]