rendering
printOn: aStream

	super printOn: aStream.
	aStream nextPut: $(;
		nextPutAll: self asColor printString;
		nextPut: $)
	