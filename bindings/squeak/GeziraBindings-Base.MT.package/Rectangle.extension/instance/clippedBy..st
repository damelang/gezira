*gezirabindings-base
clippedBy: aRectangle 
	"Like intersect: but ensures non-negative extent"
	| aPoint left right top bottom |
	aPoint := aRectangle origin.
	aPoint x > origin x ifTrue:[left := aPoint x] ifFalse:[left := origin x].
	aPoint y > origin y ifTrue:[top := aPoint y] ifFalse:[top := origin y].
	aPoint := aRectangle corner.
	aPoint x < corner x ifTrue:[right := aPoint x] ifFalse:[right := corner x].
	aPoint y < corner y ifTrue:[bottom := aPoint y] ifFalse:[bottom := corner y].
	right < left ifTrue: [right := left].
	bottom < top ifTrue: [bottom := top].
	^Rectangle
		origin: (left@top)
		corner: (right max: left)@(bottom max: top)
