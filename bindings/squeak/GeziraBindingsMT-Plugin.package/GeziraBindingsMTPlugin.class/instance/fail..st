misc
fail: aString
	self var: #aString type: 'char*'.
	self msg: aString.	
	errorMsg := aString.
	interpreterProxy success: false.
	^nil