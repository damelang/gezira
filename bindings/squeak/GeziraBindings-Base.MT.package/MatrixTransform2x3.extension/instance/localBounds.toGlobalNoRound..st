*gezirabindings-base
localBounds: srcRect toGlobalNoRound: dstRect
	"Transform aRectangle from local coordinates into the coordinates of its container.  Answer is NOT in truly global coordinates. "

	<primitive: 'primitiveTransformRectInto' module: 'GeziraBindingsMT'>
	^super localBoundsToGlobal: srcRect