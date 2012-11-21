instance creation
oval: aRectangle
	| a b c d e |
	a := 0.1464466094067263. "(1 - sin(pi/4)) / 2"
	b := 0.308658283817455.  "(1 - sin(pi/8)) / 2"
	c := 0.5.
	d := 1-b.
	e := 1-a.
	^self new points: {
		{
			0@c. 0@b. a@a. a@a. b@0. c@0.
			c@0. d@0. e@a. e@a. 1@b. 1@c.
			1@c. 1@d. e@e. e@e. d@1. c@1.
			c@1. b@1. a@e. a@e. 0@d. 0@c
		} collect: [:p | p * aRectangle extent + aRectangle origin]}