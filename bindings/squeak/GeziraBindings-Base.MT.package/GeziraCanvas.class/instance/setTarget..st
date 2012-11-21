initialize-release
setTarget: aForm
	target := aForm.
	clipAndTrans := OrderedCollection with: target boundingBox.
	self color: Color white.
