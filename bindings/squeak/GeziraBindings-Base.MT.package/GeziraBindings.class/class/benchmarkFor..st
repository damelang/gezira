preferences
benchmarkFor: milliseconds
	"GeziraBindings benchmarkFor: 1000"
	| f angle offset c frames start |
	f := Form extent: 100@100 depth: 32.
	c := GeziraCanvas on: f.
	c deferRendering: true.
	angle := 0.
	offset := 50@50.
	frames := 0.
	start := Time millisecondClockValue.
	[(Time millisecondsSince: start) <= milliseconds] whileTrue: [
		f fillBlack.
		angle := angle + 5 \\ 360.
		c preserveTransformDuring: [
			c translateBy: offset.
			1 to: 500 do: [:i | 
				c preserveTransformDuring: [
					c color: (Color h: i * 12 s: 1 v: 1).
					c rotateBy: i*18.
					c translateBy: i*0.1@0.
					c scaleBy: 0.1.
					c rotateBy: angle.
					c drawPath: GeziraCanvas star]].
			c rotateBy: angle.
			c preserveTransformDuring: [
				c color: ((Color h: angle s: 1 v: 1) alpha: 0.7).
				c scaleBy: (angle - 180) abs / 300.0 + 0.1.
				c drawPath: GeziraCanvas star]].
		c flush.
		f display.
		Display forceToScreen: f boundingBox.
		frames := frames + 1.
	].
	^frames