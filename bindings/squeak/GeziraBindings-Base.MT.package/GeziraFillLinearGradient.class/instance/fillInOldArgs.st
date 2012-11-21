accessing
fillInOldArgs
	"Calculate old delta and offset from new from/to. Should go away ASAP"
	| gradientVector gradientLength distanceFromOrigin |
	gradientVector := to - from.
	gradientLength := gradientVector r.
	distanceFromOrigin := from dotProduct: (gradientVector / gradientLength).
	self direction: gradientVector
		offset: distanceFromOrigin negated / gradientLength