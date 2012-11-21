generated
dispatchKernel: kernelName size: kernelNameSize arguments: argOops size: argCount
	"Automatically generated (see generatePluginDispatch)"
	self returnTypeC: 'void'.
	self var: #argOops type: 'sqInt*'.
	self var: #kernelName type: 'char*'.
	(self string: 'Funnel' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelFunnel: argOops size: argCount].
	(self string: 'Pipeline' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelPipeline: argOops size: argCount].
	(self string: 'Capture' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCapture: argOops size: argCount].
	(self string: 'ReadFromImageARGB32' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelReadFromImageARGB32: argOops size: argCount].
	(self string: 'WriteToImageARGB32' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelWriteToImageARGB32: argOops size: argCount].
	(self string: 'CompositeUniformColorOverImageARGB32' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeUniformColorOverImageARGB32: argOops size: argCount].
	(self string: 'ApplyColorSpans' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelApplyColorSpans: argOops size: argCount].
	(self string: 'ApplyTexture' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelApplyTexture: argOops size: argCount].
	(self string: 'BicubicFilter' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelBicubicFilter: argOops size: argCount].
	(self string: 'BilinearFilter' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelBilinearFilter: argOops size: argCount].
	(self string: 'CalculateBounds' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCalculateBounds: argOops size: argCount].
	(self string: 'ClipBeziers' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelClipBeziers: argOops size: argCount].
	(self string: 'ColorSpan' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelColorSpan: argOops size: argCount].
	(self string: 'CompositeClear' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeClear: argOops size: argCount].
	(self string: 'CompositeColorBurn' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeColorBurn: argOops size: argCount].
	(self string: 'CompositeColorDodge' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeColorDodge: argOops size: argCount].
	(self string: 'CompositeDarken' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeDarken: argOops size: argCount].
	(self string: 'CompositeDifference' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeDifference: argOops size: argCount].
	(self string: 'CompositeDst' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeDst: argOops size: argCount].
	(self string: 'CompositeDstAtop' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeDstAtop: argOops size: argCount].
	(self string: 'CompositeDstIn' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeDstIn: argOops size: argCount].
	(self string: 'CompositeDstOut' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeDstOut: argOops size: argCount].
	(self string: 'CompositeDstOver' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeDstOver: argOops size: argCount].
	(self string: 'CompositeExclusion' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeExclusion: argOops size: argCount].
	(self string: 'CompositeHardLight' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeHardLight: argOops size: argCount].
	(self string: 'CompositeInvert' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeInvert: argOops size: argCount].
	(self string: 'CompositeLighten' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeLighten: argOops size: argCount].
	(self string: 'CompositeMultiply' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeMultiply: argOops size: argCount].
	(self string: 'CompositeOver' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeOver: argOops size: argCount].
	(self string: 'CompositeOverlay' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeOverlay: argOops size: argCount].
	(self string: 'CompositePlus' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositePlus: argOops size: argCount].
	(self string: 'CompositeScreen' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeScreen: argOops size: argCount].
	(self string: 'CompositeSoftLight' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeSoftLight: argOops size: argCount].
	(self string: 'CompositeSrc' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeSrc: argOops size: argCount].
	(self string: 'CompositeSrcAtop' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeSrcAtop: argOops size: argCount].
	(self string: 'CompositeSrcIn' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeSrcIn: argOops size: argCount].
	(self string: 'CompositeSrcOut' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeSrcOut: argOops size: argCount].
	(self string: 'CompositeSubtract' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeSubtract: argOops size: argCount].
	(self string: 'CompositeTextures' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeTextures: argOops size: argCount].
	(self string: 'CompositeXor' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelCompositeXor: argOops size: argCount].
	(self string: 'ContrastiveOver' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelContrastiveOver: argOops size: argCount].
	(self string: 'GaussianBlur11x1' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelGaussianBlur11x1: argOops size: argCount].
	(self string: 'GaussianBlur1x11' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelGaussianBlur1x11: argOops size: argCount].
	(self string: 'GaussianBlur1x21' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelGaussianBlur1x21: argOops size: argCount].
	(self string: 'GaussianBlur1x5' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelGaussianBlur1x5: argOops size: argCount].
	(self string: 'GaussianBlur21x1' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelGaussianBlur21x1: argOops size: argCount].
	(self string: 'GaussianBlur5x1' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelGaussianBlur5x1: argOops size: argCount].
	(self string: 'InverseOver' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelInverseOver: argOops size: argCount].
	(self string: 'LinearGradient' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelLinearGradient: argOops size: argCount].
	(self string: 'PadGradient' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelPadGradient: argOops size: argCount].
	(self string: 'PadTexture' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelPadTexture: argOops size: argCount].
	(self string: 'RadialGradient' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelRadialGradient: argOops size: argCount].
	(self string: 'Rasterize' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelRasterize: argOops size: argCount].
	(self string: 'RectangleSpans' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelRectangleSpans: argOops size: argCount].
	(self string: 'ReflectGradient' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelReflectGradient: argOops size: argCount].
	(self string: 'ReflectTexture' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelReflectTexture: argOops size: argCount].
	(self string: 'RepeatGradient' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelRepeatGradient: argOops size: argCount].
	(self string: 'RepeatTexture' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelRepeatTexture: argOops size: argCount].
	(self string: 'StrokeBezierPath' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelStrokeBezierPath: argOops size: argCount].
	(self string: 'TransformBeziers' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelTransformBeziers: argOops size: argCount].
	(self string: 'TransformPoints' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelTransformPoints: argOops size: argCount].
	(self string: 'UniformColor' equals: kernelName len: kernelNameSize)
		ifTrue: [^self kernelUniformColor: argOops size: argCount].
	self fail: 'Unknown kernel'