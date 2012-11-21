accessing
boundsWithTransform: transform stroke: aStroke
	| bnds g |
	bnds := FloatArray new: 4.
	(g := GeziraBindings new)
		kernels: (
			g pipeline:
				{g funnel},
				(aStroke ifNil: [#()]
					ifNotNil: [aStroke strokePipelineOn: g]
				),
				{
				g transformBeziers: transform.
				g calculateBounds.
				g capture: bnds});
		pour: self floats from: 1 to: self floats size final: true;
		sync.
	^bnds first@bnds second corner: bnds third@bnds fourth