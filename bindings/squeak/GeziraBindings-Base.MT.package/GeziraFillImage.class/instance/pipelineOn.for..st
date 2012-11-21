rendering
pipelineOn: g for: aCanvas
	| t noFilter f minification level |
	t := aCanvas inverseTransformation.
	transform ifNotNil: [t := transform composedWithLocal: t].
	f := form.
	noFilter := filter == false or: [t isPureTranslation and: [t offset = t offset rounded]].
	noFilter ifTrue: [
		^g pipeline: {
			g transformPoints: t.
			g readFromImageARGB32: f.
		}].

	level := 2.
	minification := (t a11 @ t a12) r.
	[minification > level and: [f extent > (1@1)]] whileTrue: [
		mipmaps ifNil: [mipmaps := Dictionary new].			
		f := mipmaps at: level ifAbsentPut: [GeziraBindings downsample: f].
		t a11: t a11 * 0.5.
		t a12: t a12 * 0.5.
		t a21: t a21 * 0.5.
		t a22: t a22 * 0.5.
		t a13: t a13 * 0.5.
		t a23: t a23 * 0.5.
		level := level * 2].

	^g pipeline: {
		g transformPoints: t.
		g bilinearFilterT: (g readFromImageARGB32: f)}
