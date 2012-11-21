initialize-release
shutdownModule
	self export: true.
	mem isNil ifFalse: [
		self cCode: 'free (nile_shutdown (init))'.
		mem := nil].
	^true