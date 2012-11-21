instance creation
uniform: aColor
	^ GeziraFillUniform new
		setAlpha: aColor alpha
		red: aColor red
		green: aColor green
		blue: aColor blue