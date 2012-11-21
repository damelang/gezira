accessing
boundsWithTransform: transform clip: aRectangle stroke: aStroke
	"If no bound can be found within the clip rect, this answers a Rectangle with negative extent"
	| bnds g |
	bnds := FloatArray new: 4.
	(g := GeziraBindings new)
		kernels: (g pipeline:
			{g funnel},
			(aStroke ifNotNil: [
				aStroke strokePipelineOn: g]
			ifNil: [#()]),{
			g transformBeziers: transform.
			g clipBeziers: aRectangle.
			g calculateBounds.
			g capture: bnds});
		pour: self floats from: 1 to: self floats size final: true;
		sync.
	^bnds first@bnds second corner: bnds third@bnds fourth