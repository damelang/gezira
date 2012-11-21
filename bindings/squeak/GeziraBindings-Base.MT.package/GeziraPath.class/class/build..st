instance creation
build: aBlock
	| builder |
	builder := GeziraPathBuilder new.
	aBlock value: builder.
	^self new floats: builder floats