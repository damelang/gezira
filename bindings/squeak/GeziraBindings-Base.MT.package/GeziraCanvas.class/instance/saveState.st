preserve state
saveState
	"Save the state of the canvas onto the internal stack."
	previousState := self clone.
	clipAndTrans := clipAndTrans copy.
