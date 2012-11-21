primitives
primitiveNumberOfCores
	"Answer number of (virtual) cores in this machine"
	| numCPU |
	self primitive: 'primitiveNumberOfCores'.
	numCPU := self cCode: 'sysconf( _SC_NPROCESSORS_ONLN )'.
	numCPU < 1 ifTrue: [self fail: 'could not determine number of cores'. ^nil].
	^numCPU asSmallIntegerObj 
