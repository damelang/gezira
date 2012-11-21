building
close
	"Add a line from current position to first point"
	pos = (floats first @ floats second) ifFalse: [
		self vertex: 0; vertex: 0.
		stream nextPut: floats first; nextPut: floats second].