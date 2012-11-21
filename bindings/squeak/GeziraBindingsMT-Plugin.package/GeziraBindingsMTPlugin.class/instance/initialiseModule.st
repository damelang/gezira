initialize-release
initialiseModule
	self export: true.
	memSize := 0.
	mem := nil.
	threads := 0.
	init := nil.
	0 to: images sizeof / (images at: 0) sizeof - 1 do: [:i |
		self cCode: 'images[i].pixels = NULL'].
	self reset.
	^true