effects
gaussianBlur: aPath size: blurSize flatten: flattenFactor
	blurSize >= 21
		ifTrue: [^self gaussianBlur21x21: aPath flatten: flattenFactor].
	blurSize >= 11
		ifTrue: [^self gaussianBlur11x11: aPath flatten: flattenFactor].
	blurSize >= 5
		ifTrue: [^self gaussianBlur5x5: aPath flatten: flattenFactor].
