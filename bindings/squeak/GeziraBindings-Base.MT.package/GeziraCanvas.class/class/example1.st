examples
example1
	"GeziraCanvas example1"

	| f |
	f := Form extent: 500@500 depth: 32.
	(GeziraCanvas on: f)
		color: (Color red alpha: 0.5);
		translateBy: 100@100;
		drawPath: self star.
	Display getCanvas
		translucentImage: f at: 0@0;
		forceToScreen: f boundingBox.
