matrix primitives
storeRectangle: dstOop x0: x0 y0: y0 x1: x1 y1: y1
	"Check, round and store the result of a rectangle operation"
	| originOop cornerOop rectOop |
	self var: #x0 type:'double '.
	self var: #y0 type:'double '.
	self var: #x1 type:'double '.
	self var: #y1 type:'double '.
	self var: #minX type:'double '.
	self var: #maxX type:'double '.
	self var: #minY type:'double '.
	self var: #maxY type:'double '.

	interpreterProxy pushRemappableOop: dstOop.
	originOop := self makePoint: x0 and: y0.
	interpreterProxy pushRemappableOop: originOop.
	cornerOop := self makePoint: x1 and: y1.
	originOop := interpreterProxy popRemappableOop.
	rectOop := interpreterProxy popRemappableOop.
	interpreterProxy storePointer: 0 ofObject: rectOop withValue: originOop.
	interpreterProxy storePointer: 1 ofObject: rectOop withValue: cornerOop.
	^rectOop