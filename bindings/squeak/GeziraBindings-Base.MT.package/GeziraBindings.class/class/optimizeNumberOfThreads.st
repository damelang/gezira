preferences
optimizeNumberOfThreads
	"GeziraBindings optimizeNumberOfThreads"
	| benchmarks threshold good |
	benchmarks := (1 to: self cores) collect: [:threads |
		self threads: threads.
		(self benchmarkFor: 500) -> threads].
	threshold := benchmarks max key * 0.9.
	good := ((benchmarks select: [:ea | ea key > threshold]) detectMin: [:ea | ea value]) value.
	self threads: good.
	^good