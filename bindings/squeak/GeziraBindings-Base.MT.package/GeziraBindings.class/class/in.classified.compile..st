generating
in: aClassName classified: aCategory compile: aString
	"Compile aString in aCategory of aClass, but only if it is different from the current source code.
	Useful to avoid cluttering the changes file when auto-generating methods."
	| targetClass selector |
	targetClass := Smalltalk classNamed: aClassName.
	targetClass ifNil: [^self].
	selector := targetClass parserClass new parseSelector: aString.
	((targetClass includesSelector: selector)
		and: [(targetClass sourceCodeAt: selector) = aString])
			ifFalse: [targetClass compile: aString classified: aCategory]