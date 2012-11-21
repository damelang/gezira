accessing
offset
	"Deprecated, use from/to instead"
	offset ifNil: [self fillInOldArgs].
	^ offset