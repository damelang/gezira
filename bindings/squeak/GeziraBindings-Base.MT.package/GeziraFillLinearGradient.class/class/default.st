defaults
default
	"Answer a default fill of the receiver, itself a fill class."

	^ self new
		direction: 50@0 offset: 0.5;
		addStop: Color white at: 0;
		addStop: Color blue at: 0.5;
		addStop: Color black at: 1;
		yourself