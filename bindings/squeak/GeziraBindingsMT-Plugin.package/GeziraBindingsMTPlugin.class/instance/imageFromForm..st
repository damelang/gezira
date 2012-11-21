misc
imageFromForm: formOop
	| i pixels depth height width |
	self returnTypeC: 'gezira_Image_t*'.
	self var: #pixels type: 'usqInt*'.
	(interpreterProxy slotSizeOf: formOop) < 4 ifTrue: [self fail: 'invalid form'. ^nil].
	pixels := interpreterProxy fetchArray: 0 ofObject: formOop.
	i := 0.
	[i < (images sizeof / (images at: 0) sizeof)
		and: [self cCode: 'images[i].pixels != NULL']
	] whileTrue: [
		pixels = (self cCode: 'images[i].pixels')
			ifTrue: [^self cCode: '&images[i]'].
		i:= i + 1].
	i < (images sizeof / (images at: 0) sizeof)
		ifFalse: [self fail: 'too many images'. ^nil].
	width := interpreterProxy fetchInteger: 1 ofObject: formOop.
	height := interpreterProxy fetchInteger: 2 ofObject: formOop.
	depth := interpreterProxy fetchInteger: 3 ofObject: formOop.
	interpreterProxy failed ifTrue: [self fail: 'invalid form'. ^nil].
	(depth ~= 32) ifTrue: [self fail: 'form must have depth 32'. ^nil].
	self cCode: 'gezira_Image_init (&images[i], pixels, width, height, width)' inSmalltalk: [width. height].
	^self cCode: '&images[i]'