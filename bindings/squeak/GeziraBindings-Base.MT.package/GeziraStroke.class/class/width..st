instance creation
width: aNumber 
	"default stroke uses miter joints and butted caps"
	^ self width: aNumber joints: self miter caps: (self miter: 0.0)
