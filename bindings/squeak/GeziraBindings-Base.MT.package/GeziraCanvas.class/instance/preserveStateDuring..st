preserve state
preserveStateDuring: aBlock
	self saveState.
	^aBlock ensure: [self restoreState].
