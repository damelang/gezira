accessing
containsPoint: aPoint withTransform: aTransform stroke: aStroke
	| target g |
	target := Form extent: 2@2 depth: 32.	"work around gezira out-of-bounds bug"
	(g := GeziraBindings new)
		kernels: (
			g pipeline: (
				{g funnel},
				(aStroke ifNil: [#()]
					ifNotNil: [aStroke strokePipelineOn: g]
				),{
				g transformBeziers: ((MatrixTransform2x3 withOffset: aPoint negated) composedWithLocal: aTransform).
				g clipBeziers: (0@0 corner: 1@1). "target boundingBox -- work around gezira out-of-bounds bug"
				g rasterize.
				g compositeUniformColorCA: 1 cR: 1 cG: 1 cB: 1 overImageARGB32: target
			}));
		pour: self floats from: 1 to: self floats size final: true.
	"GLOG ifNil: [GLOG := FileStream fileNamed: 'glog.txt'. GLOG setToEnd].
	GLOG nextPutAll: g commandsStringC; flush."
	g sync.
	^target bits first > 0
