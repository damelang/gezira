drawing
drawPath: aPath
	"If we have a deferred renderer, append this path to its commands. Otherwise, render immediately and sync."
	| g |
	(g := deferredRenderer ifNil: [GeziraBindings new])
		appendKernels: (
			g pipeline: (
				{g funnel}
			),(
				stroke ifNil: [#()]
					ifNotNil: [stroke strokePipelineOn: g]
			),(
				clipAndTrans collect: [:each |
					each isRectangle
						ifTrue: [g clipBeziers: each]
						ifFalse: [g transformBeziers: each]]
			),(
				fill renderOn: g target: target for: self
			));
		pour: aPath from: 1 to: aPath size final: true.
	deferredRenderer
		ifNil: [g sync]
		ifNotNil: [g syncIfNeeded].
