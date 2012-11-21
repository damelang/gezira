defaults
defaultFillReplacing: aFill
	"Answer a default value to use as a fill of this type, given that a previous fill may be in place.  If replacing a radial fill, an effort is made to have one of the gradient's stop colors be the color of that uniform fill."

	| gradientFill |
	gradientFill := self new.
	gradientFill center: 0@0 radius: 200.

	(aFill isKindOf: GeziraFillGradient)
		ifTrue:
			[gradientFill stops: aFill stops]
		ifFalse:
			[(aFill isKindOf: GeziraFillUniform)
				ifTrue:
					[gradientFill addStop: aFill asColor at: 0.01]
				ifFalse:
					[gradientFill addStop: Color red at: 0.01].

			gradientFill addStop: Color white at: 0.5.
			gradientFill addStop: Color blue at: 0.99].

	^ gradientFill