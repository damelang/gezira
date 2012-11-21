misc
string: zeroTerminated equals: notTerminated len: length
	self var: #zeroTerminated type: 'char*'.
	self var: #notTerminated type: 'char*'.
	self inline: true.
	^0 = (self str: zeroTerminated n: notTerminated cmp: length)
		and: [0 = (zeroTerminated at: length)]