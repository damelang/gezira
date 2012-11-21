instance creation
rect: rect radii: anArray 
	|rs tl bl br tr |
	(anArray allSatisfy: [:r | r <= 0])
		ifTrue: [^self path: rect asGeziraPath].
	rs := anArray collect: [:r |((r max: 0.0) min: rect width * 0.5) min: rect height * 0.5].
	tl := rs first.
	bl := rs second.
	br := rs third.
	tr := rs fourth.
	^self build: [:builder | builder
		pos: rect topLeft + (0.0@tl) dir: 0.0 @ -1.0;
		right: tl; line: rect width - tl - tr;
		right: tr; line: rect height - tr - br;
		right: br; line: rect width - br - bl;
		right: bl; close
	]