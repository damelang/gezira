rendering
printOn: aStream
	from ifNil: [self fromTo].
	aStream nextPutAll: self class name;
		nextPut: $(;
		nextPutAll: from printString;
		nextPutAll: ', ';
		nextPutAll: to printString;
		nextPut: $).