building
line: length
	"append straight line segment of given length"
	length > 0 ifTrue: [self vertex: 0; vertex: 0; vertex: length].
