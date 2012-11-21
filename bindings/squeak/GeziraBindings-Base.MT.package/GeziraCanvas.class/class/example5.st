examples
example5
	"GeziraCanvas example5"

	| f |
	f := Form extent: 500@500 depth: 32.
	(GeziraCanvas on: f)
		translateBy: 100@100;
		rotateBy: 0;
		scaleBy: 0.75;
		fill: (GeziraFillRadialGradient new
			center: 0@0 radius: 200;
			addStop: Color red at: 0;
			addStop: Color yellow at: 1);
		drawRectangle: (20@20 extent: 200@200) radius: 20;
		fill: (GeziraFillLinearGradient new
			direction: 200@200 offset: 0;
			addStop: Color white at: 0;
			addStop: Color black at: 1);
		stroke: (GeziraStroke width: 6 joints: GeziraStroke miter caps: GeziraStroke miter);
		drawRectangle: (20@20 extent: 200@200) radius: 20.
	Display getCanvas
		translucentImage: f at: 0@0;
		forceToScreen: f boundingBox.
