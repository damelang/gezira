private
vertex: distance
	pos := pos + (dir * distance).
	stream nextPut: pos x; nextPut: pos y.
