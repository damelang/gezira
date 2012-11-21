rendering
renderOn: g target: targetForm for: aCanvas
	^{ g rasterize.
		g compositeUniformColorCA: alpha cR: red cG: green cB: blue overImageARGB32: targetForm }
