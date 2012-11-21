deferred rendering
flush
	deferredRenderer ifNotNil: [deferredRenderer sync]