building
left: radius
	"Turn left with given radius, sharp turn if 0"
	radius > 0 ifTrue: [
		self vertex: 0; vertex: radius.
		dir := dir y @ dir x negated.
		self vertex: radius.
	] ifFalse: [
		dir := dir y @ dir x negated.
	]