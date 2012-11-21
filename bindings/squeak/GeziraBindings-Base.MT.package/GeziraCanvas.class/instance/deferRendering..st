deferred rendering
deferRendering: aBoolean
	"If true, accumulate drawing commands in deferredRenderer until set to false"
	aBoolean
		ifTrue: [deferredRenderer ifNil: [
			deferredRenderer := GeziraBindings new]]
		ifFalse: [
			self flush.
			deferredRenderer := nil]
