defaults
default
	"Answer a default fill of the receiver, itself a fill class."

	^ self new
		center: 0@0 radius: 200;
		addStop: Color red at: 0;
		addStop: Color yellow at: 1;
		yourself