commands
kernelFunnel: argOops size: argCount
	"No arguments"
	| result |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #v type: 'nile_Process_t**'.

	argCount ~= 0
		ifTrue: [^self fail: 'Funnel takes no arguments'].

	result := self cCode: 'nile_Funnel (init)'.
	self pushKernel: result.
