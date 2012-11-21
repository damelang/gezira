generated
kernelColorSpan: argOops size: argCount
	"Automatically generated (see generatePluginKernels)"
	| result s1A s1R s1G s1B s2A s2R s2G s2B l |
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #result type: 'nile_Process_t*'.
	self var: #s1A type: 'float'.
	self var: #s1R type: 'float'.
	self var: #s1G type: 'float'.
	self var: #s1B type: 'float'.
	self var: #s2A type: 'float'.
	self var: #s2R type: 'float'.
	self var: #s2G type: 'float'.
	self var: #s2B type: 'float'.
	self var: #l type: 'float'.
	argCount ~= 9
		ifTrue: [^self fail: 'wrong argument count in ColorSpan'].
	s1A := interpreterProxy floatValueOf: (argOops at: 0).
	s1R := interpreterProxy floatValueOf: (argOops at: 1).
	s1G := interpreterProxy floatValueOf: (argOops at: 2).
	s1B := interpreterProxy floatValueOf: (argOops at: 3).
	s2A := interpreterProxy floatValueOf: (argOops at: 4).
	s2R := interpreterProxy floatValueOf: (argOops at: 5).
	s2G := interpreterProxy floatValueOf: (argOops at: 6).
	s2B := interpreterProxy floatValueOf: (argOops at: 7).
	l := interpreterProxy floatValueOf: (argOops at: 8).
	interpreterProxy failed ifTrue: [^self fail: 'wrong arguments to ColorSpan'].
	result := self cCode: 'gezira_ColorSpan(init, s1A, s1R, s1G, s1B, s2A, s2R, s2G, s2B, l)'.
	self pushKernel: result.
