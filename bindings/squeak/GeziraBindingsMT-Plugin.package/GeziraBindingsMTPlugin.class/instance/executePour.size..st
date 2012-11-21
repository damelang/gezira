commands
executePour: argOops size: argCount
	"Pour command args are (vertices start end eos)"
	| pipeline vertices start end eos |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #pipeline type: #'nile_Process_t*'.
	self var: #vertices type: #'float*'.
	argCount ~= 4
		ifTrue: [^self fail: 'wrong argument count in Pour'].
	pipeline := self topKernel.
	vertices := interpreterProxy arrayValueOf: (argOops at: 0).
	start := interpreterProxy checkedIntegerValueOf: (argOops at: 1).
	end := interpreterProxy checkedIntegerValueOf: (argOops at: 2).
	eos := interpreterProxy booleanValueOf: (argOops at: 3).
	interpreterProxy failed ifTrue: [
		^self fail: 'wrong arguments in Pour'].
	self cCode: 'nile_Funnel_pour (pipeline, vertices + start - 1, end - start + 1, eos)'
		inSmalltalk: [pipeline. vertices. start. end. eos].
	eos ifTrue: [self popKernel].