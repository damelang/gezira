commands
executeSync: argOops size: argCount
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self cCode: 'nile_sync(init)'.
	errorCode := self cCode: 'nile_status(init)'.
	errorCode ~= (self cCode: 'NILE_STATUS_OK') ifTrue: [^self fail: 'sync failed'].
	self reset.
	wasSync := true.
