building
right: radius
	"Turn right with given radius, sharp turn if 0"
	radius > 0 ifTrue: [
		self vertex: 0; vertex: radius.
		dir := dir y negated @ dir x.
		self vertex: radius.
	] ifFalse: [
		dir := dir y negated @ dir x
	]