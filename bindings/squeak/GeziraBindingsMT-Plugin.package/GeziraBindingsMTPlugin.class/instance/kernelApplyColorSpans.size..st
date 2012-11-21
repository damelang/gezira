generated
kernelApplyColorSpans: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result spans |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #spans type: 'nile_Process_t*'.
	argCount ~= 0
		ifTrue: [^self fail: 'wrong argument count in ApplyColorSpans'].
	spans := self popKernel.
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to ApplyColorSpans'].
	result := self cCode: 'gezira_ApplyColorSpans(init, spans)'.
	self pushKernel: result.
