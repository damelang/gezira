preserve state
preserveTransformDuring: aBlock
	| old |
	old := clipAndTrans copy.
	^aBlock ensure: [clipAndTrans := old].