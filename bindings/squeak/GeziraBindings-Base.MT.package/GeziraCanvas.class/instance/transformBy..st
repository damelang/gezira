transforming
transformBy: aTransform
	| prev |
	aTransform isIdentity ifTrue: [^self].
	(prev := clipAndTrans first) isRectangle
		ifTrue: [clipAndTrans addFirst: aTransform]
		ifFalse: [clipAndTrans at: 1 put: (prev composedWithLocal: aTransform)].
