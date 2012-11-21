converting
transformedBy: aTransform 
	^ self class new
		points: (self points
				collect: [:ps | ps asArray
						collect: [:p | aTransform transformPointNoRound: p]])