matrix primitives
loadArgumentMatrix: matrix
	"Load the argument matrix"
	self returnTypeC:'float *'.
	interpreterProxy failed ifTrue:[^nil].
	((interpreterProxy isWords: matrix) and:[(interpreterProxy slotSizeOf: matrix) = 6]) 
		ifFalse:[interpreterProxy primitiveFail.
				^nil].
	^self cCoerce: (interpreterProxy firstIndexableField: matrix) to:'float *'.