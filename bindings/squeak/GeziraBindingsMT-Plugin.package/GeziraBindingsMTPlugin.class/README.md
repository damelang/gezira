This plugin interfaces to Gezira. It uses a stack-based approach to assemble kernels.

Variables:
	mem    -- a chunk of memory
	nile   -- the nile instance, using the memory mem
	stack  -- an array of nile kernels
	stackP -- number of kernels on the stack

Each primitive corresponds to a particular Gezira kernel. It creates the kernel and pushes it onto the stack. Kernel arguments are passed as primitive parameters or on the stack depending on their type (kernels on the kernel stack, reals as primitive arguments). The left-most kernel argument needs to be pushed first.

The kernel primitives are generated, see GeziraBindings class>>generatePrimitives.

Example

	| target vertices |
	"Smalltalk unloadModule: 'GeziraBindings'"
	target := (Display copy: (0@0 extent: 400@300)) asFormOfDepth: 32.
	vertices := GeziraCanvas star.
	GeziraBindings new
			primTransformBeziersMA: 1.0 mB: 0.0 mC: 0.0 mD: 1.0 mE: 150.0 mF: 150.0;
			primClipBeziersMinX: 0.0 minY: 0.0 maxX: target width asFloat maxY: target height asFloat;
					primUniformColorCA: 0.5 cR: 1.0 cG: 0.0 cB: 0.0;
					primReadImageARGB32: target;
					primCompositeOver;
				primCompositeSamplers;
				primWriteImageARGB32: target;
			primRender;
		primPipeline: 3;
		primFeed: vertices asFloatArray from: 1 to: vertices size by: 6;
		primSync.
	target display
