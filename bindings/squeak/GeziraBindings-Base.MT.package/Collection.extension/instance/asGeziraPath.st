*gezirabindings-base
asGeziraPath
	^self anyOne isNumber
		ifTrue: [GeziraPath new floats: self]
		ifFalse: [GeziraPath new points: self]
