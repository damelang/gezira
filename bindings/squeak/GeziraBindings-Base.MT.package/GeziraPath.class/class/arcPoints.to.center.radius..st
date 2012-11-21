instance creation
arcPoints: from to: to center: centerPoint radius: radius

	| x y p0 p2 p1 points more last step |
	step := Float pi/4.
	points := WriteStream on: (Array new: ((to - from)/step) asInteger * 3).
	x := from.
	y := x + step.
	p0 := ((x cos@x sin) * radius) + centerPoint.
	"points nextPut: centerPoint; nextPut: centerPoint; nextPut: p0."
	more := true.
	last := false.
	[more] whileTrue: [
		p2 := ((y cos@y sin) * radius) + centerPoint.
		p1 := (((-0.5 * (x cos + y cos) + (2 * (0.5*(x+y)) cos))@(-0.5 * (x sin + y sin) + (2 * (0.5 * (x + y)) sin))) * radius) + centerPoint.
		points nextPut: p0; nextPut: p1; nextPut: p2.
		x := y.
		last ifTrue: [more := false].
		y := (x + step >= to) ifTrue: [last := true. to] ifFalse: [x + step].
		p0 := p2.
	].
	"points nextPut: p0; nextPut: p0; nextPut: centerPoint."
	^ points contents.
	

