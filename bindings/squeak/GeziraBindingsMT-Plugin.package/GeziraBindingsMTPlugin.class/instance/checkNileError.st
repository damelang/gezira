misc
checkNileError
	errorCode := self cCode: 'nile_status(init)'.
	errorCode ~= (self cCode: 'NILE_STATUS_OK') ifTrue: [
		self fail: 'nile error'].
