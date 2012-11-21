queries
fillStyle
	"Answer a symbol characterizing the style of fill.  This should by rights be reimplemented in each of the GeziraFill subclasses, but in order to minimize contamination of the Gezira classes, the work is currently handled by a single method.  Nonmodular but expedient..."

	^ LFillStyleType fillStyleForFill: self