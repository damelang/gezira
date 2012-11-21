instance creation
rect: rect radii: anArray edges: bs
	|rs tl bl br tr size open segments b blocks last ret |
	open := (bs occurrencesOf: false) > 0.
	open ifFalse: [^ {self rect: rect radii: anArray}].

	"When it is either #(top bottom) or #(left right), the result needs to be an array of two elements."
	size := (bs = #(true false true false) or: [bs = #(false true false true)]) ifTrue: [2] ifFalse: [1].
	rs := anArray collect: [:r |((r max: 0.0) min: rect width * 0.5) min: rect height * 0.5].
	tl := rs first.
	bl := rs second.
	br := rs third.
	tr := rs fourth.
	"Construct the potential 8 (4 edges and 4 corners) segments.  When the radius is 0 for a corner, it does not contain any points; so the number of points from this method is not a constant (24).  So, we collect each of these 8 things separately first."
	segments := Array new: 8.
	b := GeziraPathBuilder new.
	b pos: rect topLeft + (tl@0) dir: 1@0.
	blocks := {[b line: rect width - tl - tr]. [b right: tr]. [b line: rect height - tr - br]. [b right: br].
				[b line: rect width - br - bl]. [b right: bl]. [b line: rect height - bl - tl]. [b right: tl]}.
	last := b count + 1.
	1 to: 8 do: [:i |
		(blocks at: i) value.
		segments at: i put: (b floats copyFrom: last to: b count).
		last := b count + 1].
	"When the result is one path, start from the empty edge and go around the segments."
	size = 1 ifTrue: [
		ret := Array new writeStream.
		0 to: 3 do: [:i |
			(bs atWrap: i + 1) ifTrue: [
				ret nextPutAll: (segments atWrap: (i * 2) + 1)].
			ret nextPutAll: (segments atWrap: (i * 2) + 2)].
		^ {self new floats: ret contents}].
	"When the result is two paths."
	^ #(0 2) collect: [:i |
			ret := Array new writeStream.
			ret nextPutAll: (segments atWrap: (i * 2)).
			ret nextPutAll: (segments atWrap: (i * 2) + 1).
			ret nextPutAll: (segments atWrap: (i * 2) + 2).
			self new floats: ret contents]
