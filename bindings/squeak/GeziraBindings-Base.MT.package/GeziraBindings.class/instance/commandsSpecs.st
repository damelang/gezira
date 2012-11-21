printing
commandsSpecs
	| specs |
	specs := {
		#Funnel -> #().
		#ReadFromImageARGB32->#((Form 'f')).
		#WriteToImageARGB32->#((Form 'f')).
		#CompositeUniformColorOverImageARGB32 -> #((Real 'a') (Real 'r') (Real 'g') (Real 'b') (Form 'f')).
		#Capture->#((Array 'a')).
	} as: Dictionary. 
	self class kernelDefinitionsDo: [:k :d | specs at: k put: d].
	^specs