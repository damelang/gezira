primitives
pluginName
	self class methodsDo: [:method |
		method primitive = 117
			ifTrue: [^method literals first first]].
	^self error: 'no primitives defined'