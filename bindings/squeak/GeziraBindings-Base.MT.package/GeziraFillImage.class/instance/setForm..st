accessing
setForm: aForm
	form := aForm depth < 32
		ifTrue: [(aForm asFormOfDepth: 32)fixAlpha]
		ifFalse: [aForm].
	opaque := false.
	mipmaps := nil.