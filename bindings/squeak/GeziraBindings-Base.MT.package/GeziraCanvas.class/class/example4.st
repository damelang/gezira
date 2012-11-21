examples
example4
	"GeziraCanvas example4"

	| f |
	f := Form extent: 500@500 depth: 32.
	(GeziraCanvas on: f)
		fill: (GeziraFillLinearGradient new
			direction: 50@0 offset: 0.5;
			addStop: Color blue at: 0;			"-infinity to 0"
			addStop: Color red at: 0.01;
			addStop: Color yellow at: 0.99;
			addStop: Color green at: 1);		"1 to infinity"
		translateBy: 100@100;
		rotateBy: 10;
		scaleBy: 0.75;
		drawPath: self star.
	Display getCanvas
		translucentImage: f at: 0@0;
		forceToScreen: f boundingBox.
