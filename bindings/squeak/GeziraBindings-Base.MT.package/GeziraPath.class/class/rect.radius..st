instance creation
rect: rect radius: radius
	| r |
	radius <= 0
		ifTrue: [^self path: rect asGeziraPath].
	r := (radius min: rect width * 0.5) min: rect height * 0.5.
	^ self build: [:builder | builder
		pos: rect topLeft + (0.0 @ r) dir: (0.0 @ -1.0);
		right: r; line: rect width - (2.0 * r);
		right: r; line: rect height - (2.0 * r);
		right: r; line: rect width - (2.0 * r);
		right: r; close
	]