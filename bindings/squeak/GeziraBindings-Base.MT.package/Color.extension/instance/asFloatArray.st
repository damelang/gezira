*gezirabindings-base
asFloatArray
	^FloatArray
		with: (self privateRed / ComponentMax)
		with: (self privateGreen asFloat / ComponentMax)
		with: (self privateBlue asFloat / ComponentMax)
		with: self alpha
