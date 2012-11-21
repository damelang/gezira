matrix primitives
loadArgumentPoint: point
	"Load the argument point into m23ArgX and m23ArgY"
	| oop isInt |
	interpreterProxy failed ifTrue:[^nil].
	"Check class of point"
	(interpreterProxy fetchClassOf: point) = (interpreterProxy classPoint) 
		ifFalse:[^interpreterProxy primitiveFail].
	"Load X value"
	oop := interpreterProxy fetchPointer: 0 ofObject: point.
	isInt := interpreterProxy isIntegerObject: oop.
	(isInt or:[interpreterProxy isFloatObject: oop])
		ifFalse:[^interpreterProxy primitiveFail].
	isInt
		ifTrue:[m23ArgX := interpreterProxy integerValueOf: oop]
		ifFalse:[m23ArgX := interpreterProxy floatValueOf: oop].

	"Load Y value"
	oop := interpreterProxy fetchPointer: 1 ofObject: point.
	isInt := interpreterProxy isIntegerObject: oop.
	(isInt or:[interpreterProxy isFloatObject: oop])
		ifFalse:[^interpreterProxy primitiveFail].
	isInt
		ifTrue:[m23ArgY := interpreterProxy integerValueOf: oop]
		ifFalse:[m23ArgY := interpreterProxy floatValueOf: oop].

