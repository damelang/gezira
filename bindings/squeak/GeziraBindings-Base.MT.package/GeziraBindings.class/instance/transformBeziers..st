building
transformBeziers: aMatrix
	^self transformBeziersMA: aMatrix a11
		mB: aMatrix a21
		mC: aMatrix a12
		mD: aMatrix a22
		mE: aMatrix a13
		mF: aMatrix a23