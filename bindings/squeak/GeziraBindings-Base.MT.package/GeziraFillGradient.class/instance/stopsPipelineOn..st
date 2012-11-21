rendering
stopsPipelineOn: g
	stops size < 2 ifTrue: [^self error: 'too few stops'].
	^g pipeline: (
		(2 to: stops size) collect: [:i |
			| prev next l s1 s2 |
			prev := stops at: i - 1.
			next := stops at: i.
			l := next key - prev key.
			s1 := prev value.
			s2 := next value.
			g colorSpanS1A: s1 fourth s1R: s1 first s1G: s1 second s1B: s1 third
				s2A: s2 fourth s2R: s2 first s2G: s2 second s2B: s2 third
				l: l])