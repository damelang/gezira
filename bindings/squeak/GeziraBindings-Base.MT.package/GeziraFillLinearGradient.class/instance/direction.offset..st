accessing
direction: aPoint offset: zeroToOne
	"Deprecated, use from/to instead"
	delta := aPoint / (aPoint dotProduct: aPoint) asFloat.
	offset := zeroToOne asFloat.
