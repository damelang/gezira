defaults
defaultFillReplacing: aFill
	"Answer a default value to use as a fill of this type, given that a previous fill may be in place.  This mechanism has not been properly elaborated yet, and may be superceded by a policy of remembering entire fills in properties so if the style is called upon again, the earlier settings will not be lost..."

	(aFill isKindOf: self) ifTrue:
		[^ self uniform: aFill asColor].
	(aFill isKindOf: GeziraFillGradient) ifTrue:
		[^ self uniform: (Color colorFrom: aFill stops first value)].

	^ self default