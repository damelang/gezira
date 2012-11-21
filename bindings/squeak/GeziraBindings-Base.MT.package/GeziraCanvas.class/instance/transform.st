accessing
transform
	| t |
	t := nil.
	clipAndTrans reverseDo: [:each | each isRectangle ifFalse: [
		t := t ifNil: [each] ifNotNil: [t composedWithLocal: each]]].
	^t ifNil: [MatrixTransform2x3 identity]