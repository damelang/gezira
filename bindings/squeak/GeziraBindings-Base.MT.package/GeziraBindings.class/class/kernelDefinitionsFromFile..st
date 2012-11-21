parsing
kernelDefinitionsFromFile: aFileName
	"parses gezira.h but excludes systemKernels"

	"Clipboard clipboardText: (self kernelDefinitionsFromFile: 'vm/src/plugins/GeziraBindingsMT/gezira/c/gezira.h')"
	| in l parens sorted exclude |
	parens := {$( -> 1. ${ -> 1. $} -> -1. $) -> -1. $; -> -1} as: Dictionary.
	in := FileStream readOnlyFileNamed: aFileName.
	in wantsLineEndConversion: true.
	exclude := self systemKernels asSet.
	sorted := SortedCollection new.
	[ 
		[(l := in nextLine) notNil] whileTrue: [
			(l isEmpty or: [l first = $#]) ifFalse: [
				[(l inject: 1 into: [:p :c | p + (parens at: c ifAbsent: [0])]) = 0]
					whileFalse: [l := l, in nextLine withBlanksTrimmed].
			
				(l beginsWith: 'nile_Process_t *gezira_') ifFalse: [self error: 'parsing failed'].
				l := l allButFirst: 23.
				l := l allButLast.
				#(' (' '(' 'nile_Process_t *p,' '' 'nile_Process_t *p' '' 'float v_' 'Real ' 'nile_Process_t *v_' 'Kernel ')
					pairsDo: [:find :replace | l := l copyReplaceAll: find with: replace].
				exclude remove: (l copyUpTo: $()
					ifAbsent: [sorted add: l].
			]
		]
	] ensure: [in close].
	exclude ifNotEmpty: [exclude inspect].
	^ String streamContents: [:out | 
		sorted do: [:each | out nextPutAll: each; cr]]
