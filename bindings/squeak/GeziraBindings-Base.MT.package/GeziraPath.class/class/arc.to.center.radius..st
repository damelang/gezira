instance creation
arc: x to: y center: c radius: r

	| a |
	a := self arcPoints: x to: y center: c radius: r.
	^ self new points: {(Array with: c with: c with: a first), a, (Array with: a last with: a last with: c)}.
