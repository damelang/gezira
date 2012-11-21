accessing
clip
	^clipAndTrans first isRectangle
		ifTrue: [clipAndTrans first]
		ifFalse: [clipAndTrans first globalBoundsToLocal: clipAndTrans second]