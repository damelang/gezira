*gezirabindings-base
isAxisAligning
	"Return true if a transformed rectangle will still be axis-aligned, i.e. translated, scaled, and/or rotated by multiples of 90 degrees"
	^(self a12 = 0.0 and: [self a21 = 0.0])
		or: [self a11 = 0.0 and: [self a22 = 0.0]]