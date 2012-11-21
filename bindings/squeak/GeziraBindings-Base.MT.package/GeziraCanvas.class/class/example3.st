examples
example3
	"GeziraCanvas example3"
	| f angle offset c frames time |
	"Smalltalk unloadModule: 'GeziraBindings'."
	f := Form extent: 500@500 depth: 32.
	c := GeziraCanvas on: f.
	angle := 0.
	offset := 250@250.

	frames := 0.
	time := Time millisecondClockValue.
	[Sensor anyButtonPressed] whileFalse: [
		f fillWhite.
		angle := angle + 5 \\ 360.
		c preserveTransformDuring: [
			c translateBy: offset.
			1 to: 10 do: [:i | 
				c preserveTransformDuring: [
					c color: ((Color h: i * 36 s: 1 v: 1) alpha: 0.5).
					c rotateBy: i*36.
					c translateBy: 100@0.
					c scaleBy: 0.2.
					c rotateBy: angle.
					c drawPath: self star]].
			c rotateBy: angle.
			c preserveTransformDuring: [
				c color: ((Color h: angle s: 1 v: 1) alpha: 0.5).
				c scaleBy: (angle - 180) abs / 100.0 + 0.1.
				c drawPath: self star]].
		f display.
		Display forceToScreen: f boundingBox.
		"Sensor waitClickButton."
		frames := frames + 1.
		(frames * 1000 / ((Time millisecondsSince: time) asFloat) roundTo: 0.01) printString, '    ' displayAt: 0@600.

	].
	Display restore