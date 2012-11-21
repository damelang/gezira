*gezirabindings-base
localBoundsToGlobalNoRound: aRectangle
		"Transform aRectangle from local coordinates into the coordinates of its container.  Answer is NOT in truly global coordinates. "

	^self localBounds: aRectangle toGlobalNoRound: Rectangle new