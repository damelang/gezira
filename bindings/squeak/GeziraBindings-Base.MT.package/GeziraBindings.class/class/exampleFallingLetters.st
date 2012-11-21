example
exampleFallingLetters
	"GeziraBindings exampleFallingLetters"

	| target font scale paths letters scene g em frames start threads color speed transform angle angles m |
	target := Form extent: 600@600 depth: 32.
	em := 16.
	font := TTFontDescription descriptionFullNamed: 'Times New Roman'.
	scale := MatrixTransform2x3 withScale: (1 @ -1) * em / font unitsPerEm.
	paths := ($a to: $z) collect: [:c | ((font at: c) asGeziraPath transformedBy: scale) floats].
	angles := (1 to: 360) collect: [:a |
		m := MatrixTransform2x3 withAngle: a.
		{m a11. m a21. m a12. m a22}].
	g := GeziraBindings new.

	"clear target"
	g	kernels: (
			g pipeline: {
				g funnel.
				g rectangleSpansMinX: 0 minY: 0 maxX: target width maxY: target height. 
				g compositeUniformColorCA: 1 cR: 1 cG: 1 cB: 1 overImageARGB32: target});
		pour: FloatArray new.

	"render letters, collect transform nodes"
	letters := (1 to: 5000) collect: [:i |
		color := Color random.
		g appendKernels: (
			g pipeline: {
				g funnel.
				transform := g transformBeziers: (MatrixTransform2x3 withOffset: target width atRandom @ target height atRandom).
				g clipBeziers: target boundingBox.
				g rasterize.
				g compositeUniformColorCA: 1 cR: color red cG: color green cB: color blue overImageARGB32: target});
			pour: paths atRandom.
		{
		"1: transform"	transform first.
		"2: speed"		20 atRandom * 0.1 + 0.1.
		"3: angle"		360 atRandom.
		}].

	scene := g kernels.
	threads := g threadsDefault.
	frames := 0.
	start := Time millisecondClockValue.
	[threads = 0 | Sensor anyButtonPressed] whileFalse: [
		"animate"
		letters do: [:letter |
			transform := letter at: 1.
			speed := letter at: 2.
			angle := letter at: 3 put: (letter at: 3) + 5 \\ 360.
			transform at: 8 put: (transform at: 8) + speed \\ (target height + em). "fall"
			1 to: 4 do: [:i |
				transform at: i + 2 put: ((angles at: angle + 1) at: i)]].
		"render"
		g	kernels: scene; 
			threads: threads;
			sync.
		"and show"
		Display getCanvas drawImage: target at: 0@0.
		"also show fps"
		frames := frames + 1.
		threads asString, ': ', (frames * 1000 / ((Time millisecondsSince: start) asFloat) roundTo: 0.01) printString, '    ' displayAt: 0@target height.
		Sensor peekKeyboardEvent ifNotNilDo: [:e |
			e third >= $0 asInteger ifTrue: [
				threads := e third - $0 asInteger max: 0].
			frames := 0.
			start := Time millisecondClockValue]].
	Display restore.
	^scene
