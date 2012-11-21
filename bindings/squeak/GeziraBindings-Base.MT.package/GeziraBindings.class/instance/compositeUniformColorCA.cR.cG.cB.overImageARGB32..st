building
compositeUniformColorCA: cA cR: cR cG: cG cB: cB overImageARGB32: aForm 
	"This is an optimization for
				{#Kernel. #UniformColor. cA asFloat. cR asFloat. cG asFloat. cB asFloat}.
				{#Kernel. #ReadFromImageARGB32. aForm}.
				{#Kernel. #CompositeOver}.
			{#Kernel. #CompositeTextures}.
		{#Kernel. #ApplyTexture}.
		{#Kernel. #WriteToImageARGB32. aForm}.
	"
	aForm unhibernate.
	^ {{#Kernel. #CompositeUniformColorOverImageARGB32. cA asFloat. cR asFloat. cG asFloat. cB asFloat. aForm}}