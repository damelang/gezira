matrix primitives
makePoint: x and: y
	"Store the result of a previous operation."
	| point xx yy |
	self var: #x declareC: 'double x'.
	self var: #y declareC: 'double y'.
	point := interpreterProxy instantiateClass: interpreterProxy classPoint indexableSize: 2.
	interpreterProxy pushRemappableOop: point.
	xx := interpreterProxy floatObjectOf: x.
	interpreterProxy pushRemappableOop: xx.
	yy := interpreterProxy floatObjectOf: y.
	xx := interpreterProxy popRemappableOop.
	point := interpreterProxy popRemappableOop.
	interpreterProxy storePointer: 0 ofObject: point withValue: xx.
	interpreterProxy storePointer: 1 ofObject: point withValue: yy.
	^ point.
