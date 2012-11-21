translation
version
	| pkg wc version |
	pkg := PackageOrganizer default packageOfClass: self.
	wc := (MCPackage named: pkg packageName) workingCopy.
	version := wc ancestors first name copyAfterLast: $-.
	wc modified ifTrue: [version := version, '*'].
	^version