clipping
clipBy: aRectangle
	| current |
	(current := clipAndTrans at: 1) isRectangle
		ifTrue: [clipAndTrans at: 1 put: (current clippedBy: aRectangle)]
		ifFalse: [
			current isPureTranslation
				ifTrue: [clipAndTrans at: 2
					put: ((clipAndTrans at: 2) clippedBy: (aRectangle translateBy: current offset))]
				ifFalse: [
					current isAxisAligning
						ifTrue: [clipAndTrans at: 2
							put: ((clipAndTrans at: 2) clippedBy: (Rectangle encompassing:
								{current localPointToGlobal: aRectangle origin.
								 current localPointToGlobal: aRectangle corner}))]
						ifFalse: [clipAndTrans addFirst: (self clip clippedBy: aRectangle)]]].