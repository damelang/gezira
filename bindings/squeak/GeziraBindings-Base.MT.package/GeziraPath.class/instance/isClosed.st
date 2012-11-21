testing
isClosed
	| s first last |
	s := self floats size.
	first := (floats at: 1) @ (floats at: 2).
	last := (floats at: s-1) @ (floats at: s).
	^first = last