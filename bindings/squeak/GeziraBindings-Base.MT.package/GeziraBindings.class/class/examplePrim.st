example
examplePrim
	"Demos what actually gets send to the plugin - it's in postfix notation"
	"GeziraBindings examplePrim"
	| target vertices |
	target := Form extent: 400@300 depth: 32.
	vertices := GeziraCanvas star.
	GeziraBindings new
		primExecuteThreads: 1 memory: 5000000 commands:  {
				{#Kernel. #Funnel}.
				{#Kernel. #TransformBeziers. 1.0. 0.0. 0.0. 1.0. 150.0. 150.0}.
				{#Kernel. #ClipBeziers. 0.0. 0.0. target width asFloat. target height asFloat}.
				{#Kernel. #Rasterize}.
						{#Kernel. #UniformColor. 0.5. 1.0. 0.0. 0.0}.
						{#Kernel. #ReadFromImageARGB32. target}.
						{#Kernel. #CompositeOver}.
					{#Kernel. #CompositeTextures}.
				{#Kernel. #ApplyTexture}.
				{#Kernel. #WriteToImageARGB32. target}.
			{#Kernel. #Pipeline. 6}.
			{#Pour. vertices asFloatArray. 1. vertices size. true}.
		}.
	Display getCanvas translucentImage: target at: 0@0
