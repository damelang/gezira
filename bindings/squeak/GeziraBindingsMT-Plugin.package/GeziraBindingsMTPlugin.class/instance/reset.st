initialize-release
reset
	| i |
	stackP := 0.
	errorMsg := nil.
	errorItem := 0.
	errorCode := self cCode: 'NILE_STATUS_OK'.
	i := 0.
	[i < (images sizeof / (images at: 0) sizeof)
		and: [self cCode: 'images[i].pixels != NULL']
	] whileTrue: [
		self cCode: 'gezira_Image_done (&images[i])'.
		self cCode: 'images[i].pixels = NULL'.
		i:= i + 1].
