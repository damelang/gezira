building
pipeline: anArray
	| stream |
	stream := (Array new: 100) writeStream.
	anArray do: [:cmds | stream nextPutAll: cmds].
	stream nextPut: {#Kernel. #Pipeline. anArray size}.
	^stream contents