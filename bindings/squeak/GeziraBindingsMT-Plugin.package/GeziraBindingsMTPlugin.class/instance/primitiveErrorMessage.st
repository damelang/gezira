primitives
primitiveErrorMessage
	| msgLength msgOop msgPtr |
	self primitive: 'primitiveErrorMessage'.
	self var: #msgPtr type: #'char*'.
	msgLength := 0.
	errorMsg ~= nil ifTrue: [msgLength := errorMsg strlen].
	msgOop := interpreterProxy instantiateClass: interpreterProxy classString indexableSize: msgLength.
	msgLength > 0 ifTrue:[
		msgPtr := interpreterProxy firstIndexableField: msgOop.
		msgPtr str: errorMsg ncpy: msgLength].
	^msgOop