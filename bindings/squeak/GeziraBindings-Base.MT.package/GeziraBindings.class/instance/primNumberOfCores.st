primitives
primNumberOfCores
	<primitive: 'primitiveNumberOfCores' module: 'GeziraBindingsMT'>
	^self pluginMissing ifFalse: [self primitiveFailed]