/* Automatically generated from Squeak on 20 July 2012 3:06:01 pm 
   by VMMaker 4.9.6
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif
#include "gezira.h"
#include "gezira-image.h"
#include <unistd.h>

#include "sqMemoryAccess.h"


/*** Constants ***/

/*** Function Prototypes ***/
static sqInt checkNileError(void);
static void dispatchKernelsizeargumentssize(char*kernelName, sqInt kernelNameSize, sqInt*argOops, sqInt argCount);
static void executeCommand(sqInt commandArrayOop);
static void executeKernelsize(sqInt*argOops, sqInt argCount);
static void executePoursize(sqInt*argOops, sqInt argCount);
static void executeSyncsize(sqInt*argOops, sqInt argCount);
static sqInt fail(char*aString);
#pragma export on
EXPORT(const char*) getModuleName(void);
#pragma export off
static sqInt halt(void);
static gezira_Image_t* imageFromForm(sqInt formOop);
#pragma export on
EXPORT(sqInt) initialiseModule(void);
#pragma export off
static void kernelApplyColorSpanssize(sqInt*argOops, sqInt argCount);
static void kernelApplyTexturesize(sqInt*argOops, sqInt argCount);
static void kernelBicubicFiltersize(sqInt*argOops, sqInt argCount);
static void kernelBilinearFiltersize(sqInt*argOops, sqInt argCount);
static void kernelCalculateBoundssize(sqInt*argOops, sqInt argCount);
static void kernelCapturesize(sqInt*argOops, sqInt argCount);
static void kernelClipBezierssize(sqInt*argOops, sqInt argCount);
static void kernelColorSpansize(sqInt*argOops, sqInt argCount);
static void kernelCompositeClearsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeColorBurnsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeColorDodgesize(sqInt*argOops, sqInt argCount);
static void kernelCompositeDarkensize(sqInt*argOops, sqInt argCount);
static void kernelCompositeDifferencesize(sqInt*argOops, sqInt argCount);
static void kernelCompositeDstsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeDstAtopsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeDstInsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeDstOutsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeDstOversize(sqInt*argOops, sqInt argCount);
static void kernelCompositeExclusionsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeHardLightsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeInvertsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeLightensize(sqInt*argOops, sqInt argCount);
static void kernelCompositeMultiplysize(sqInt*argOops, sqInt argCount);
static void kernelCompositeOversize(sqInt*argOops, sqInt argCount);
static void kernelCompositeOverlaysize(sqInt*argOops, sqInt argCount);
static void kernelCompositePlussize(sqInt*argOops, sqInt argCount);
static void kernelCompositeScreensize(sqInt*argOops, sqInt argCount);
static void kernelCompositeSoftLightsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeSrcsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeSrcAtopsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeSrcInsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeSrcOutsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeSubtractsize(sqInt*argOops, sqInt argCount);
static void kernelCompositeTexturessize(sqInt*argOops, sqInt argCount);
static void kernelCompositeUniformColorOverImageARGB32size(sqInt*argOops, sqInt argCount);
static void kernelCompositeXorsize(sqInt*argOops, sqInt argCount);
static void kernelContrastiveOversize(sqInt*argOops, sqInt argCount);
static void kernelFunnelsize(sqInt*argOops, sqInt argCount);
static void kernelGaussianBlur11x1size(sqInt*argOops, sqInt argCount);
static void kernelGaussianBlur1x11size(sqInt*argOops, sqInt argCount);
static void kernelGaussianBlur1x21size(sqInt*argOops, sqInt argCount);
static void kernelGaussianBlur1x5size(sqInt*argOops, sqInt argCount);
static void kernelGaussianBlur21x1size(sqInt*argOops, sqInt argCount);
static void kernelGaussianBlur5x1size(sqInt*argOops, sqInt argCount);
static void kernelInverseOversize(sqInt*argOops, sqInt argCount);
static void kernelLinearGradientsize(sqInt*argOops, sqInt argCount);
static void kernelPadGradientsize(sqInt*argOops, sqInt argCount);
static void kernelPadTexturesize(sqInt*argOops, sqInt argCount);
static void kernelPipelinesize(sqInt*argOops, sqInt argCount);
static void kernelRadialGradientsize(sqInt*argOops, sqInt argCount);
static void kernelRasterizesize(sqInt*argOops, sqInt argCount);
static void kernelReadFromImageARGB32size(sqInt*argOops, sqInt argCount);
static void kernelRectangleSpanssize(sqInt*argOops, sqInt argCount);
static void kernelReflectGradientsize(sqInt*argOops, sqInt argCount);
static void kernelReflectTexturesize(sqInt*argOops, sqInt argCount);
static void kernelRepeatGradientsize(sqInt*argOops, sqInt argCount);
static void kernelRepeatTexturesize(sqInt*argOops, sqInt argCount);
static void kernelStrokeBezierPathsize(sqInt*argOops, sqInt argCount);
static void kernelTransformBezierssize(sqInt*argOops, sqInt argCount);
static void kernelTransformPointssize(sqInt*argOops, sqInt argCount);
static void kernelUniformColorsize(sqInt*argOops, sqInt argCount);
static void kernelWriteToImageARGB32size(sqInt*argOops, sqInt argCount);
static sqInt loadArgumentPoint(sqInt point);
static sqInt makePointand(double x, double y);
static sqInt matrix2x3TransformPoint(float *m);
static sqInt msg(char *s);
#pragma export on
EXPORT(sqInt) primitiveErrorCode(void);
EXPORT(sqInt) primitiveErrorItem(void);
EXPORT(sqInt) primitiveErrorMessage(void);
EXPORT(sqInt) primitiveExecuteThreadsMemCmds(void);
EXPORT(sqInt) primitiveNumberOfCores(void);
EXPORT(sqInt) primitiveTransformPoint(void);
EXPORT(sqInt) primitiveTransformRectInto(void);
#pragma export off
static sqInt reset(void);
#pragma export on
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
EXPORT(sqInt) shutdownModule(void);
#pragma export off
static sqInt storeRectanglex0y0x1y1(sqInt dstOop, double  x0, double  y0, double  x1, double  y1);
/*** Variables ***/
static sqInt errorCode;
static sqInt errorItem;
static char* errorMsg;
static gezira_Image_t images[100];
static nile_Process_t* init;

#ifdef SQUEAK_BUILTIN_PLUGIN
extern
#endif
struct VirtualMachine* interpreterProxy;
static double m23ArgX;
static double m23ArgY;
static double m23ResultX;
static double m23ResultY;
static char* mem;
static sqInt memSize;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"GeziraBindingsMT bf.24 20 July 2012 (i)"
#else
	"GeziraBindingsMT bf.24 20 July 2012 (e)"
#endif
;
static nile_Process_t* stack[100];
static int stackP;
static sqInt threads;
static sqInt wasSync;


static sqInt checkNileError(void) {
	errorCode = nile_status(init);
	if (errorCode != (NILE_STATUS_OK)) {
		fail("nile error");
	}
}


/*	Automatically generated (see generatePluginDispatch) */

static void dispatchKernelsizeargumentssize(char*kernelName, sqInt kernelNameSize, sqInt*argOops, sqInt argCount) {
	if ((0 == (strncmp("Funnel", kernelName, kernelNameSize))) && (0 == ("Funnel"[kernelNameSize]))) {
		kernelFunnelsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("Pipeline", kernelName, kernelNameSize))) && (0 == ("Pipeline"[kernelNameSize]))) {
		kernelPipelinesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("Capture", kernelName, kernelNameSize))) && (0 == ("Capture"[kernelNameSize]))) {
		kernelCapturesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("ReadFromImageARGB32", kernelName, kernelNameSize))) && (0 == ("ReadFromImageARGB32"[kernelNameSize]))) {
		kernelReadFromImageARGB32size(argOops, argCount); return;
	}
	if ((0 == (strncmp("WriteToImageARGB32", kernelName, kernelNameSize))) && (0 == ("WriteToImageARGB32"[kernelNameSize]))) {
		kernelWriteToImageARGB32size(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeUniformColorOverImageARGB32", kernelName, kernelNameSize))) && (0 == ("CompositeUniformColorOverImageARGB32"[kernelNameSize]))) {
		kernelCompositeUniformColorOverImageARGB32size(argOops, argCount); return;
	}
	if ((0 == (strncmp("ApplyColorSpans", kernelName, kernelNameSize))) && (0 == ("ApplyColorSpans"[kernelNameSize]))) {
		kernelApplyColorSpanssize(argOops, argCount); return;
	}
	if ((0 == (strncmp("ApplyTexture", kernelName, kernelNameSize))) && (0 == ("ApplyTexture"[kernelNameSize]))) {
		kernelApplyTexturesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("BicubicFilter", kernelName, kernelNameSize))) && (0 == ("BicubicFilter"[kernelNameSize]))) {
		kernelBicubicFiltersize(argOops, argCount); return;
	}
	if ((0 == (strncmp("BilinearFilter", kernelName, kernelNameSize))) && (0 == ("BilinearFilter"[kernelNameSize]))) {
		kernelBilinearFiltersize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CalculateBounds", kernelName, kernelNameSize))) && (0 == ("CalculateBounds"[kernelNameSize]))) {
		kernelCalculateBoundssize(argOops, argCount); return;
	}
	if ((0 == (strncmp("ClipBeziers", kernelName, kernelNameSize))) && (0 == ("ClipBeziers"[kernelNameSize]))) {
		kernelClipBezierssize(argOops, argCount); return;
	}
	if ((0 == (strncmp("ColorSpan", kernelName, kernelNameSize))) && (0 == ("ColorSpan"[kernelNameSize]))) {
		kernelColorSpansize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeClear", kernelName, kernelNameSize))) && (0 == ("CompositeClear"[kernelNameSize]))) {
		kernelCompositeClearsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeColorBurn", kernelName, kernelNameSize))) && (0 == ("CompositeColorBurn"[kernelNameSize]))) {
		kernelCompositeColorBurnsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeColorDodge", kernelName, kernelNameSize))) && (0 == ("CompositeColorDodge"[kernelNameSize]))) {
		kernelCompositeColorDodgesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeDarken", kernelName, kernelNameSize))) && (0 == ("CompositeDarken"[kernelNameSize]))) {
		kernelCompositeDarkensize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeDifference", kernelName, kernelNameSize))) && (0 == ("CompositeDifference"[kernelNameSize]))) {
		kernelCompositeDifferencesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeDst", kernelName, kernelNameSize))) && (0 == ("CompositeDst"[kernelNameSize]))) {
		kernelCompositeDstsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeDstAtop", kernelName, kernelNameSize))) && (0 == ("CompositeDstAtop"[kernelNameSize]))) {
		kernelCompositeDstAtopsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeDstIn", kernelName, kernelNameSize))) && (0 == ("CompositeDstIn"[kernelNameSize]))) {
		kernelCompositeDstInsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeDstOut", kernelName, kernelNameSize))) && (0 == ("CompositeDstOut"[kernelNameSize]))) {
		kernelCompositeDstOutsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeDstOver", kernelName, kernelNameSize))) && (0 == ("CompositeDstOver"[kernelNameSize]))) {
		kernelCompositeDstOversize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeExclusion", kernelName, kernelNameSize))) && (0 == ("CompositeExclusion"[kernelNameSize]))) {
		kernelCompositeExclusionsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeHardLight", kernelName, kernelNameSize))) && (0 == ("CompositeHardLight"[kernelNameSize]))) {
		kernelCompositeHardLightsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeInvert", kernelName, kernelNameSize))) && (0 == ("CompositeInvert"[kernelNameSize]))) {
		kernelCompositeInvertsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeLighten", kernelName, kernelNameSize))) && (0 == ("CompositeLighten"[kernelNameSize]))) {
		kernelCompositeLightensize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeMultiply", kernelName, kernelNameSize))) && (0 == ("CompositeMultiply"[kernelNameSize]))) {
		kernelCompositeMultiplysize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeOver", kernelName, kernelNameSize))) && (0 == ("CompositeOver"[kernelNameSize]))) {
		kernelCompositeOversize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeOverlay", kernelName, kernelNameSize))) && (0 == ("CompositeOverlay"[kernelNameSize]))) {
		kernelCompositeOverlaysize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositePlus", kernelName, kernelNameSize))) && (0 == ("CompositePlus"[kernelNameSize]))) {
		kernelCompositePlussize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeScreen", kernelName, kernelNameSize))) && (0 == ("CompositeScreen"[kernelNameSize]))) {
		kernelCompositeScreensize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeSoftLight", kernelName, kernelNameSize))) && (0 == ("CompositeSoftLight"[kernelNameSize]))) {
		kernelCompositeSoftLightsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeSrc", kernelName, kernelNameSize))) && (0 == ("CompositeSrc"[kernelNameSize]))) {
		kernelCompositeSrcsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeSrcAtop", kernelName, kernelNameSize))) && (0 == ("CompositeSrcAtop"[kernelNameSize]))) {
		kernelCompositeSrcAtopsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeSrcIn", kernelName, kernelNameSize))) && (0 == ("CompositeSrcIn"[kernelNameSize]))) {
		kernelCompositeSrcInsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeSrcOut", kernelName, kernelNameSize))) && (0 == ("CompositeSrcOut"[kernelNameSize]))) {
		kernelCompositeSrcOutsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeSubtract", kernelName, kernelNameSize))) && (0 == ("CompositeSubtract"[kernelNameSize]))) {
		kernelCompositeSubtractsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeTextures", kernelName, kernelNameSize))) && (0 == ("CompositeTextures"[kernelNameSize]))) {
		kernelCompositeTexturessize(argOops, argCount); return;
	}
	if ((0 == (strncmp("CompositeXor", kernelName, kernelNameSize))) && (0 == ("CompositeXor"[kernelNameSize]))) {
		kernelCompositeXorsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("ContrastiveOver", kernelName, kernelNameSize))) && (0 == ("ContrastiveOver"[kernelNameSize]))) {
		kernelContrastiveOversize(argOops, argCount); return;
	}
	if ((0 == (strncmp("GaussianBlur11x1", kernelName, kernelNameSize))) && (0 == ("GaussianBlur11x1"[kernelNameSize]))) {
		kernelGaussianBlur11x1size(argOops, argCount); return;
	}
	if ((0 == (strncmp("GaussianBlur1x11", kernelName, kernelNameSize))) && (0 == ("GaussianBlur1x11"[kernelNameSize]))) {
		kernelGaussianBlur1x11size(argOops, argCount); return;
	}
	if ((0 == (strncmp("GaussianBlur1x21", kernelName, kernelNameSize))) && (0 == ("GaussianBlur1x21"[kernelNameSize]))) {
		kernelGaussianBlur1x21size(argOops, argCount); return;
	}
	if ((0 == (strncmp("GaussianBlur1x5", kernelName, kernelNameSize))) && (0 == ("GaussianBlur1x5"[kernelNameSize]))) {
		kernelGaussianBlur1x5size(argOops, argCount); return;
	}
	if ((0 == (strncmp("GaussianBlur21x1", kernelName, kernelNameSize))) && (0 == ("GaussianBlur21x1"[kernelNameSize]))) {
		kernelGaussianBlur21x1size(argOops, argCount); return;
	}
	if ((0 == (strncmp("GaussianBlur5x1", kernelName, kernelNameSize))) && (0 == ("GaussianBlur5x1"[kernelNameSize]))) {
		kernelGaussianBlur5x1size(argOops, argCount); return;
	}
	if ((0 == (strncmp("InverseOver", kernelName, kernelNameSize))) && (0 == ("InverseOver"[kernelNameSize]))) {
		kernelInverseOversize(argOops, argCount); return;
	}
	if ((0 == (strncmp("LinearGradient", kernelName, kernelNameSize))) && (0 == ("LinearGradient"[kernelNameSize]))) {
		kernelLinearGradientsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("PadGradient", kernelName, kernelNameSize))) && (0 == ("PadGradient"[kernelNameSize]))) {
		kernelPadGradientsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("PadTexture", kernelName, kernelNameSize))) && (0 == ("PadTexture"[kernelNameSize]))) {
		kernelPadTexturesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("RadialGradient", kernelName, kernelNameSize))) && (0 == ("RadialGradient"[kernelNameSize]))) {
		kernelRadialGradientsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("Rasterize", kernelName, kernelNameSize))) && (0 == ("Rasterize"[kernelNameSize]))) {
		kernelRasterizesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("RectangleSpans", kernelName, kernelNameSize))) && (0 == ("RectangleSpans"[kernelNameSize]))) {
		kernelRectangleSpanssize(argOops, argCount); return;
	}
	if ((0 == (strncmp("ReflectGradient", kernelName, kernelNameSize))) && (0 == ("ReflectGradient"[kernelNameSize]))) {
		kernelReflectGradientsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("ReflectTexture", kernelName, kernelNameSize))) && (0 == ("ReflectTexture"[kernelNameSize]))) {
		kernelReflectTexturesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("RepeatGradient", kernelName, kernelNameSize))) && (0 == ("RepeatGradient"[kernelNameSize]))) {
		kernelRepeatGradientsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("RepeatTexture", kernelName, kernelNameSize))) && (0 == ("RepeatTexture"[kernelNameSize]))) {
		kernelRepeatTexturesize(argOops, argCount); return;
	}
	if ((0 == (strncmp("StrokeBezierPath", kernelName, kernelNameSize))) && (0 == ("StrokeBezierPath"[kernelNameSize]))) {
		kernelStrokeBezierPathsize(argOops, argCount); return;
	}
	if ((0 == (strncmp("TransformBeziers", kernelName, kernelNameSize))) && (0 == ("TransformBeziers"[kernelNameSize]))) {
		kernelTransformBezierssize(argOops, argCount); return;
	}
	if ((0 == (strncmp("TransformPoints", kernelName, kernelNameSize))) && (0 == ("TransformPoints"[kernelNameSize]))) {
		kernelTransformPointssize(argOops, argCount); return;
	}
	if ((0 == (strncmp("UniformColor", kernelName, kernelNameSize))) && (0 == ("UniformColor"[kernelNameSize]))) {
		kernelUniformColorsize(argOops, argCount); return;
	}
	fail("Unknown kernel");
}


/*	Command is an Array like #('Cmd' arg1 arg2). Dispatch to the actual commands */

static void executeCommand(sqInt commandArrayOop) {
	sqInt*commandArray;
	char*commandName;
	sqInt commandNameSize;
	sqInt commandArraySize;
	sqInt commandNameOop;

	commandArraySize = interpreterProxy->slotSizeOf(commandArrayOop);
	if (!(commandArraySize > 0)) {
		fail("Empty command"); return;
	}
	commandArray = interpreterProxy->firstIndexableField(commandArrayOop);
	commandNameOop = interpreterProxy->fetchPointerofObject(0, commandArrayOop);
	if (!(interpreterProxy->isBytes(commandNameOop))) {
		fail("Command name not a String"); return;
	}
	commandName = interpreterProxy->firstIndexableField(commandNameOop);
	commandNameSize = interpreterProxy->slotSizeOf(commandNameOop);
	if ((0 == (strncmp("Kernel", commandName, commandNameSize))) && (0 == ("Kernel"[commandNameSize]))) {
		executeKernelsize(commandArray + 1, commandArraySize - 1); return;
	}
	if ((0 == (strncmp("Pour", commandName, commandNameSize))) && (0 == ("Pour"[commandNameSize]))) {
		executePoursize(commandArray + 1, commandArraySize - 1); return;
	}
	if ((0 == (strncmp("Sync", commandName, commandNameSize))) && (0 == ("Sync"[commandNameSize]))) {
		executeSyncsize(commandArray + 1, commandArraySize - 1); return;
	}
	fail("Unknown command");
}


/*	A kernel command looks like #('KernelName' arg1 arg2). Dispatch on the name. */

static void executeKernelsize(sqInt*argOops, sqInt argCount) {
	sqInt kernelNameOop;
	char*kernelName;
	sqInt kernelNameSize;

	if (argCount < 1) {
		fail("No kernel name given"); return;
	}
	kernelNameOop = argOops[0];
	if (!(interpreterProxy->isBytes(kernelNameOop))) {
		fail("kernel name not a String"); return;
	}
	kernelName = interpreterProxy->firstIndexableField(kernelNameOop);
	kernelNameSize = interpreterProxy->slotSizeOf(kernelNameOop);
	dispatchKernelsizeargumentssize(kernelName, kernelNameSize, argOops + 1, argCount - 1);
}


/*	Pour command args are (vertices start end eos) */

static void executePoursize(sqInt*argOops, sqInt argCount) {
	sqInt start;
	sqInt eos;
	sqInt end;
	nile_Process_t* pipeline;
	float*vertices;

	if (argCount != 4) {
		fail("wrong argument count in Pour"); return;
	}
	/* begin topKernel */
	if (stackP < 1) {
		fail("empty stack");
		pipeline = null;
		goto l2;
	}
	pipeline = stack[stackP - 1];
l2:	/* end topKernel */;
	vertices = interpreterProxy->arrayValueOf(argOops[0]);
	start = interpreterProxy->checkedIntegerValueOf(argOops[1]);
	end = interpreterProxy->checkedIntegerValueOf(argOops[2]);
	eos = interpreterProxy->booleanValueOf(argOops[3]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments in Pour"); return;
	}
	nile_Funnel_pour (pipeline, vertices + start - 1, end - start + 1, eos);
	if (eos) {
		/* begin popKernel */
		if (!(stackP > 0)) {
			fail("kernel stack underflow");
			goto l1;
		}
		stackP -= 1;
		stack[stackP];
	l1:	/* end popKernel */;
	}
}

static void executeSyncsize(sqInt*argOops, sqInt argCount) {
	nile_sync(init);
	errorCode = nile_status(init);
	if (errorCode != (NILE_STATUS_OK)) {
		fail("sync failed"); return;
	}
	reset();
	wasSync = 1;
}

static sqInt fail(char*aString) {
	msg(aString);
	errorMsg = aString;
	interpreterProxy->success(0);
	return null;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*) getModuleName(void) {
	return moduleName;
}

static sqInt halt(void) {
	;
}

static gezira_Image_t* imageFromForm(sqInt formOop) {
	sqInt i;
	usqInt*pixels;
	sqInt width;
	sqInt depth;
	sqInt height;

	if ((interpreterProxy->slotSizeOf(formOop)) < 4) {
		fail("invalid form");
		return null;
	}
	pixels = interpreterProxy->fetchArrayofObject(0, formOop);
	i = 0;
	while ((i < ((sizeof(images)) / (sizeof(images[0])))) && (images[i].pixels != NULL)) {
		if (pixels == (images[i].pixels)) {
			return &images[i];
		}
		i += 1;
	}
	if (!(i < ((sizeof(images)) / (sizeof(images[0]))))) {
		fail("too many images");
		return null;
	}
	width = interpreterProxy->fetchIntegerofObject(1, formOop);
	height = interpreterProxy->fetchIntegerofObject(2, formOop);
	depth = interpreterProxy->fetchIntegerofObject(3, formOop);
	if (interpreterProxy->failed()) {
		fail("invalid form");
		return null;
	}
	if (depth != 32) {
		fail("form must have depth 32");
		return null;
	}
	gezira_Image_init (&images[i], pixels, width, height, width);
	return &images[i];
}

EXPORT(sqInt) initialiseModule(void) {
	sqInt i;

	memSize = 0;
	mem = null;
	threads = 0;
	init = null;
	for (i = 0; i <= (((sizeof(images)) / (sizeof(images[0]))) - 1); i += 1) {
		images[i].pixels = NULL;
	}
	reset();
	return 1;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelApplyColorSpanssize(sqInt*argOops, sqInt argCount) {
	nile_Process_t* spans;
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in ApplyColorSpans"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		spans = null;
		goto l1;
	}
	stackP -= 1;
	spans = stack[stackP];
l1:	/* end popKernel */;
	if (interpreterProxy->failed()) {
		fail("wrong arguments to ApplyColorSpans"); return;
	}
	result = gezira_ApplyColorSpans(init, spans);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelApplyTexturesize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 0) {
		fail("wrong argument count in ApplyTexture"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	if (interpreterProxy->failed()) {
		fail("wrong arguments to ApplyTexture"); return;
	}
	result = gezira_ApplyTexture(init, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelBicubicFiltersize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 0) {
		fail("wrong argument count in BicubicFilter"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	if (interpreterProxy->failed()) {
		fail("wrong arguments to BicubicFilter"); return;
	}
	result = gezira_BicubicFilter(init, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelBilinearFiltersize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 0) {
		fail("wrong argument count in BilinearFilter"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	if (interpreterProxy->failed()) {
		fail("wrong arguments to BilinearFilter"); return;
	}
	result = gezira_BilinearFilter(init, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCalculateBoundssize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CalculateBounds"); return;
	}
	result = gezira_CalculateBounds(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Argument is a FloatArray */

static void kernelCapturesize(sqInt*argOops, sqInt argCount) {
	float*array;
	sqInt arraySize;
	static int n;
	sqInt arrayOop;
	nile_Process_t*result;

	if (argCount != 1) {
		fail("wrong kernel argument count in Capture"); return;
	}
	arrayOop = argOops[0];
	array = interpreterProxy->arrayValueOf(arrayOop);
	if (interpreterProxy->failed()) {
		fail("invalid array"); return;
	}
	arraySize = interpreterProxy->slotSizeOf(arrayOop);
	n = 0;
	result = nile_Capture (init, array, &n, arraySize);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelClipBezierssize(sqInt*argOops, sqInt argCount) {
	float minY;
	float minX;
	nile_Process_t*result;
	float maxX;
	float maxY;

	if (argCount != 4) {
		fail("wrong argument count in ClipBeziers"); return;
	}
	minX = interpreterProxy->floatValueOf(argOops[0]);
	minY = interpreterProxy->floatValueOf(argOops[1]);
	maxX = interpreterProxy->floatValueOf(argOops[2]);
	maxY = interpreterProxy->floatValueOf(argOops[3]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to ClipBeziers"); return;
	}
	result = gezira_ClipBeziers(init, minX, minY, maxX, maxY);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelColorSpansize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;
	float s2G;
	float s1G;
	float l;
	float s2R;
	float s2B;
	float s2A;
	float s1R;
	float s1B;
	float s1A;

	if (argCount != 9) {
		fail("wrong argument count in ColorSpan"); return;
	}
	s1A = interpreterProxy->floatValueOf(argOops[0]);
	s1R = interpreterProxy->floatValueOf(argOops[1]);
	s1G = interpreterProxy->floatValueOf(argOops[2]);
	s1B = interpreterProxy->floatValueOf(argOops[3]);
	s2A = interpreterProxy->floatValueOf(argOops[4]);
	s2R = interpreterProxy->floatValueOf(argOops[5]);
	s2G = interpreterProxy->floatValueOf(argOops[6]);
	s2B = interpreterProxy->floatValueOf(argOops[7]);
	l = interpreterProxy->floatValueOf(argOops[8]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to ColorSpan"); return;
	}
	result = gezira_ColorSpan(init, s1A, s1R, s1G, s1B, s2A, s2R, s2G, s2B, l);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeClearsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeClear"); return;
	}
	result = gezira_CompositeClear(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeColorBurnsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeColorBurn"); return;
	}
	result = gezira_CompositeColorBurn(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeColorDodgesize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeColorDodge"); return;
	}
	result = gezira_CompositeColorDodge(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeDarkensize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeDarken"); return;
	}
	result = gezira_CompositeDarken(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeDifferencesize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeDifference"); return;
	}
	result = gezira_CompositeDifference(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeDstsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeDst"); return;
	}
	result = gezira_CompositeDst(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeDstAtopsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeDstAtop"); return;
	}
	result = gezira_CompositeDstAtop(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeDstInsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeDstIn"); return;
	}
	result = gezira_CompositeDstIn(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeDstOutsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeDstOut"); return;
	}
	result = gezira_CompositeDstOut(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeDstOversize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeDstOver"); return;
	}
	result = gezira_CompositeDstOver(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeExclusionsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeExclusion"); return;
	}
	result = gezira_CompositeExclusion(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeHardLightsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeHardLight"); return;
	}
	result = gezira_CompositeHardLight(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeInvertsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeInvert"); return;
	}
	result = gezira_CompositeInvert(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeLightensize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeLighten"); return;
	}
	result = gezira_CompositeLighten(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeMultiplysize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeMultiply"); return;
	}
	result = gezira_CompositeMultiply(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeOversize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeOver"); return;
	}
	result = gezira_CompositeOver(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeOverlaysize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeOverlay"); return;
	}
	result = gezira_CompositeOverlay(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositePlussize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositePlus"); return;
	}
	result = gezira_CompositePlus(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeScreensize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeScreen"); return;
	}
	result = gezira_CompositeScreen(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeSoftLightsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeSoftLight"); return;
	}
	result = gezira_CompositeSoftLight(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeSrcsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeSrc"); return;
	}
	result = gezira_CompositeSrc(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeSrcAtopsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeSrcAtop"); return;
	}
	result = gezira_CompositeSrcAtop(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeSrcInsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeSrcIn"); return;
	}
	result = gezira_CompositeSrcIn(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeSrcOutsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeSrcOut"); return;
	}
	result = gezira_CompositeSrcOut(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeSubtractsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeSubtract"); return;
	}
	result = gezira_CompositeSubtract(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeTexturessize(sqInt*argOops, sqInt argCount) {
	nile_Process_t* t2;
	nile_Process_t* t1;
	nile_Process_t*result;
	nile_Process_t* c;

	if (argCount != 0) {
		fail("wrong argument count in CompositeTextures"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		c = null;
		goto l1;
	}
	stackP -= 1;
	c = stack[stackP];
l1:	/* end popKernel */;
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t2 = null;
		goto l2;
	}
	stackP -= 1;
	t2 = stack[stackP];
l2:	/* end popKernel */;
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t1 = null;
		goto l3;
	}
	stackP -= 1;
	t1 = stack[stackP];
l3:	/* end popKernel */;
	if (interpreterProxy->failed()) {
		fail("wrong arguments to CompositeTextures"); return;
	}
	result = gezira_CompositeTextures(init, t1, t2, c);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l4;
	}
	stack[stackP] = result;
	stackP += 1;
l4:	/* end pushKernel: */;
}


/*	Argument is a Form and 4 Floats for the color */

static void kernelCompositeUniformColorOverImageARGB32size(sqInt*argOops, sqInt argCount) {
	float red;
	float green;
	float blue;
	float alpha;
	gezira_Image_t*image;
	nile_Process_t*result;

	if (argCount != 5) {
		fail("wrong kernel argument count in WriteToImageARGB32UniformColor"); return;
	}
	alpha = interpreterProxy->floatValueOf(argOops[0]);
	red = interpreterProxy->floatValueOf(argOops[1]);
	green = interpreterProxy->floatValueOf(argOops[2]);
	blue = interpreterProxy->floatValueOf(argOops[3]);
	if (interpreterProxy->failed()) {
		fail("invalid color components in WriteToImageARGB32UniformColor"); return;
	}
	image = imageFromForm(argOops[4]);
	if (interpreterProxy->failed()) {
		return;
	}
	result = gezira_CompositeUniformColorOverImage_ARGB32 (init, image, alpha, red, green, blue);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelCompositeXorsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in CompositeXor"); return;
	}
	result = gezira_CompositeXor(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelContrastiveOversize(sqInt*argOops, sqInt argCount) {
	float a;
	nile_Process_t*result;

	if (argCount != 1) {
		fail("wrong argument count in ContrastiveOver"); return;
	}
	a = interpreterProxy->floatValueOf(argOops[0]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to ContrastiveOver"); return;
	}
	result = gezira_ContrastiveOver(init, a);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	No arguments */

static void kernelFunnelsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("Funnel takes no arguments"); return;
	}
	result = nile_Funnel (init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelGaussianBlur11x1size(sqInt*argOops, sqInt argCount) {
	float f;
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 1) {
		fail("wrong argument count in GaussianBlur11x1"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	f = interpreterProxy->floatValueOf(argOops[0]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to GaussianBlur11x1"); return;
	}
	result = gezira_GaussianBlur11x1(init, f, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelGaussianBlur1x11size(sqInt*argOops, sqInt argCount) {
	float f;
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 1) {
		fail("wrong argument count in GaussianBlur1x11"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	f = interpreterProxy->floatValueOf(argOops[0]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to GaussianBlur1x11"); return;
	}
	result = gezira_GaussianBlur1x11(init, f, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelGaussianBlur1x21size(sqInt*argOops, sqInt argCount) {
	float f;
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 1) {
		fail("wrong argument count in GaussianBlur1x21"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	f = interpreterProxy->floatValueOf(argOops[0]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to GaussianBlur1x21"); return;
	}
	result = gezira_GaussianBlur1x21(init, f, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelGaussianBlur1x5size(sqInt*argOops, sqInt argCount) {
	float f;
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 1) {
		fail("wrong argument count in GaussianBlur1x5"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	f = interpreterProxy->floatValueOf(argOops[0]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to GaussianBlur1x5"); return;
	}
	result = gezira_GaussianBlur1x5(init, f, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelGaussianBlur21x1size(sqInt*argOops, sqInt argCount) {
	float f;
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 1) {
		fail("wrong argument count in GaussianBlur21x1"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	f = interpreterProxy->floatValueOf(argOops[0]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to GaussianBlur21x1"); return;
	}
	result = gezira_GaussianBlur21x1(init, f, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelGaussianBlur5x1size(sqInt*argOops, sqInt argCount) {
	float f;
	nile_Process_t*result;
	nile_Process_t* t;

	if (argCount != 1) {
		fail("wrong argument count in GaussianBlur5x1"); return;
	}
	/* begin popKernel */
	if (!(stackP > 0)) {
		fail("kernel stack underflow");
		t = null;
		goto l1;
	}
	stackP -= 1;
	t = stack[stackP];
l1:	/* end popKernel */;
	f = interpreterProxy->floatValueOf(argOops[0]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to GaussianBlur5x1"); return;
	}
	result = gezira_GaussianBlur5x1(init, f, t);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelInverseOversize(sqInt*argOops, sqInt argCount) {
	float a;
	nile_Process_t*result;

	if (argCount != 1) {
		fail("wrong argument count in InverseOver"); return;
	}
	a = interpreterProxy->floatValueOf(argOops[0]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to InverseOver"); return;
	}
	result = gezira_InverseOver(init, a);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelLinearGradientsize(sqInt*argOops, sqInt argCount) {
	float sX;
	float eY;
	float eX;
	nile_Process_t*result;
	float sY;

	if (argCount != 4) {
		fail("wrong argument count in LinearGradient"); return;
	}
	sX = interpreterProxy->floatValueOf(argOops[0]);
	sY = interpreterProxy->floatValueOf(argOops[1]);
	eX = interpreterProxy->floatValueOf(argOops[2]);
	eY = interpreterProxy->floatValueOf(argOops[3]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to LinearGradient"); return;
	}
	result = gezira_LinearGradient(init, sX, sY, eX, eY);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelPadGradientsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in PadGradient"); return;
	}
	result = gezira_PadGradient(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelPadTexturesize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;
	float dX;
	float dY;

	if (argCount != 2) {
		fail("wrong argument count in PadTexture"); return;
	}
	dX = interpreterProxy->floatValueOf(argOops[0]);
	dY = interpreterProxy->floatValueOf(argOops[1]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to PadTexture"); return;
	}
	result = gezira_PadTexture(init, dX, dY);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Argument is an integer, pops n kernels */

static void kernelPipelinesize(sqInt*argOops, sqInt argCount) {
	sqInt n;
	nile_Process_t** v;
	nile_Process_t*result;

	if (argCount != 1) {
		fail("wrong kernel argument count in Pipeline"); return;
	}
	n = interpreterProxy->checkedIntegerValueOf(argOops[0]);
	/* begin popKernels: */
	if (!(stackP >= n)) {
		fail("kernel stack underflow");
		v = null;
		goto l1;
	}
	stackP -= n;
	v = stack + stackP;
l1:	/* end popKernels: */;
	if (interpreterProxy->failed()) {
		return;
	}
	result = nile_Process_pipe_v (v, n);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l2;
	}
	stack[stackP] = result;
	stackP += 1;
l2:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelRadialGradientsize(sqInt*argOops, sqInt argCount) {
	float r;
	float cY;
	float cX;
	nile_Process_t*result;

	if (argCount != 3) {
		fail("wrong argument count in RadialGradient"); return;
	}
	cX = interpreterProxy->floatValueOf(argOops[0]);
	cY = interpreterProxy->floatValueOf(argOops[1]);
	r = interpreterProxy->floatValueOf(argOops[2]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to RadialGradient"); return;
	}
	result = gezira_RadialGradient(init, cX, cY, r);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelRasterizesize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in Rasterize"); return;
	}
	result = gezira_Rasterize(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Argument is a Form */

static void kernelReadFromImageARGB32size(sqInt*argOops, sqInt argCount) {
	gezira_Image_t*image;
	nile_Process_t*result;

	if (argCount != 1) {
		fail("wrong kernel argument count in ReadFromImageARGB32"); return;
	}
	image = imageFromForm(argOops[0]);
	if (interpreterProxy->failed()) {
		return;
	}
	result = gezira_ReadFromImage_ARGB32 (init, image, 1);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelRectangleSpanssize(sqInt*argOops, sqInt argCount) {
	float minY;
	float minX;
	nile_Process_t*result;
	float maxX;
	float maxY;

	if (argCount != 4) {
		fail("wrong argument count in RectangleSpans"); return;
	}
	minX = interpreterProxy->floatValueOf(argOops[0]);
	minY = interpreterProxy->floatValueOf(argOops[1]);
	maxX = interpreterProxy->floatValueOf(argOops[2]);
	maxY = interpreterProxy->floatValueOf(argOops[3]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to RectangleSpans"); return;
	}
	result = gezira_RectangleSpans(init, minX, minY, maxX, maxY);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelReflectGradientsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in ReflectGradient"); return;
	}
	result = gezira_ReflectGradient(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelReflectTexturesize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;
	float dX;
	float dY;

	if (argCount != 2) {
		fail("wrong argument count in ReflectTexture"); return;
	}
	dX = interpreterProxy->floatValueOf(argOops[0]);
	dY = interpreterProxy->floatValueOf(argOops[1]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to ReflectTexture"); return;
	}
	result = gezira_ReflectTexture(init, dX, dY);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelRepeatGradientsize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;

	if (argCount != 0) {
		fail("wrong argument count in RepeatGradient"); return;
	}
	result = gezira_RepeatGradient(init);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelRepeatTexturesize(sqInt*argOops, sqInt argCount) {
	nile_Process_t*result;
	float dX;
	float dY;

	if (argCount != 2) {
		fail("wrong argument count in RepeatTexture"); return;
	}
	dX = interpreterProxy->floatValueOf(argOops[0]);
	dY = interpreterProxy->floatValueOf(argOops[1]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to RepeatTexture"); return;
	}
	result = gezira_RepeatTexture(init, dX, dY);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelStrokeBezierPathsize(sqInt*argOops, sqInt argCount) {
	float w;
	nile_Process_t*result;
	float l;
	float c;

	if (argCount != 3) {
		fail("wrong argument count in StrokeBezierPath"); return;
	}
	w = interpreterProxy->floatValueOf(argOops[0]);
	l = interpreterProxy->floatValueOf(argOops[1]);
	c = interpreterProxy->floatValueOf(argOops[2]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to StrokeBezierPath"); return;
	}
	result = gezira_StrokeBezierPath(init, w, l, c);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelTransformBezierssize(sqInt*argOops, sqInt argCount) {
	float mE;
	float mD;
	float mC;
	float mB;
	float mA;
	nile_Process_t*result;
	float mF;

	if (argCount != 6) {
		fail("wrong argument count in TransformBeziers"); return;
	}
	mA = interpreterProxy->floatValueOf(argOops[0]);
	mB = interpreterProxy->floatValueOf(argOops[1]);
	mC = interpreterProxy->floatValueOf(argOops[2]);
	mD = interpreterProxy->floatValueOf(argOops[3]);
	mE = interpreterProxy->floatValueOf(argOops[4]);
	mF = interpreterProxy->floatValueOf(argOops[5]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to TransformBeziers"); return;
	}
	result = gezira_TransformBeziers(init, mA, mB, mC, mD, mE, mF);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelTransformPointssize(sqInt*argOops, sqInt argCount) {
	float mE;
	float mD;
	float mC;
	float mB;
	float mA;
	nile_Process_t*result;
	float mF;

	if (argCount != 6) {
		fail("wrong argument count in TransformPoints"); return;
	}
	mA = interpreterProxy->floatValueOf(argOops[0]);
	mB = interpreterProxy->floatValueOf(argOops[1]);
	mC = interpreterProxy->floatValueOf(argOops[2]);
	mD = interpreterProxy->floatValueOf(argOops[3]);
	mE = interpreterProxy->floatValueOf(argOops[4]);
	mF = interpreterProxy->floatValueOf(argOops[5]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to TransformPoints"); return;
	}
	result = gezira_TransformPoints(init, mA, mB, mC, mD, mE, mF);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Automatically generated (see generatePluginKernels) */

static void kernelUniformColorsize(sqInt*argOops, sqInt argCount) {
	float cA;
	float cR;
	float cG;
	nile_Process_t*result;
	float cB;

	if (argCount != 4) {
		fail("wrong argument count in UniformColor"); return;
	}
	cA = interpreterProxy->floatValueOf(argOops[0]);
	cR = interpreterProxy->floatValueOf(argOops[1]);
	cG = interpreterProxy->floatValueOf(argOops[2]);
	cB = interpreterProxy->floatValueOf(argOops[3]);
	if (interpreterProxy->failed()) {
		fail("wrong arguments to UniformColor"); return;
	}
	result = gezira_UniformColor(init, cA, cR, cG, cB);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Argument is a Form */

static void kernelWriteToImageARGB32size(sqInt*argOops, sqInt argCount) {
	gezira_Image_t*image;
	nile_Process_t*result;

	if (argCount != 1) {
		fail("wrong kernel argument count in WriteToImageARGB32"); return;
	}
	image = imageFromForm(argOops[0]);
	if (interpreterProxy->failed()) {
		return;
	}
	result = gezira_WriteToImage_ARGB32 (init, image);
	/* begin pushKernel: */
	if (!(stackP < ((sizeof(stack)) / (sizeof(stack[0]))))) {
		fail("kernel stack overflow");
		goto l1;
	}
	stack[stackP] = result;
	stackP += 1;
l1:	/* end pushKernel: */;
}


/*	Load the argument point into m23ArgX and m23ArgY */

static sqInt loadArgumentPoint(sqInt point) {
	sqInt oop;
	sqInt isInt;

	if (interpreterProxy->failed()) {
		return null;
	}
	if (!((interpreterProxy->fetchClassOf(point)) == (interpreterProxy->classPoint()))) {
		return interpreterProxy->primitiveFail();
	}
	oop = interpreterProxy->fetchPointerofObject(0, point);
	isInt = (oop & 1);
	if (!(isInt || (interpreterProxy->isFloatObject(oop)))) {
		return interpreterProxy->primitiveFail();
	}
	if (isInt) {
		m23ArgX = (oop >> 1);
	} else {
		m23ArgX = interpreterProxy->floatValueOf(oop);
	}
	oop = interpreterProxy->fetchPointerofObject(1, point);
	isInt = (oop & 1);
	if (!(isInt || (interpreterProxy->isFloatObject(oop)))) {
		return interpreterProxy->primitiveFail();
	}
	if (isInt) {
		m23ArgY = (oop >> 1);
	} else {
		m23ArgY = interpreterProxy->floatValueOf(oop);
	}
}


/*	Store the result of a previous operation. */

static sqInt makePointand(double x, double y) {
	sqInt xx;
	sqInt yy;
	sqInt point;

	point = interpreterProxy->instantiateClassindexableSize(interpreterProxy->classPoint(), 2);
	interpreterProxy->pushRemappableOop(point);
	xx = interpreterProxy->floatObjectOf(x);
	interpreterProxy->pushRemappableOop(xx);
	yy = interpreterProxy->floatObjectOf(y);
	xx = interpreterProxy->popRemappableOop();
	point = interpreterProxy->popRemappableOop();
	interpreterProxy->storePointerofObjectwithValue(0, point, xx);
	interpreterProxy->storePointerofObjectwithValue(1, point, yy);
	return point;
}


/*	Transform the pre-loaded argument point by the given matrix */

static sqInt matrix2x3TransformPoint(float *m) {
	m23ResultX = ((m23ArgX * (m[0])) + (m23ArgY * (m[1]))) + (m[2]);
	m23ResultY = ((m23ArgX * (m[3])) + (m23ArgY * (m[4]))) + (m[5]);
}

static sqInt msg(char *s) {
	fprintf(stderr, "\n%s: %s", moduleName, s);
}

EXPORT(sqInt) primitiveErrorCode(void) {
	sqInt _return_value;

	_return_value = interpreterProxy->integerObjectOf(errorCode);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(1, _return_value);
	return null;
}

EXPORT(sqInt) primitiveErrorItem(void) {
	sqInt _return_value;

	_return_value = interpreterProxy->integerObjectOf(errorItem);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(1, _return_value);
	return null;
}

EXPORT(sqInt) primitiveErrorMessage(void) {
	sqInt msgOop;
	char*msgPtr;
	sqInt msgLength;

	msgLength = 0;
	if (errorMsg != null) {
		msgLength = strlen(errorMsg);
	}
	msgOop = interpreterProxy->instantiateClassindexableSize(interpreterProxy->classString(), msgLength);
	if (msgLength > 0) {
		msgPtr = interpreterProxy->firstIndexableField(msgOop);
		strncpy(msgPtr, errorMsg, msgLength);
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(1, msgOop);
	return null;
}


/*	argument is an array of commands like #(#(Cmd1 args) #(Cmd2 args)) */

EXPORT(sqInt) primitiveExecuteThreadsMemCmds(void) {
	sqInt i;
	sqInt allCommandsSize;
	sqInt*allCommands;
	sqInt eachCommandOop;
	sqInt newThreads;
	sqInt newMemSize;
	sqInt allCommandsOop;

	newThreads = interpreterProxy->stackIntegerValue(2);
	newMemSize = interpreterProxy->stackIntegerValue(1);
	allCommandsOop = interpreterProxy->stackValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(interpreterProxy->isArray(allCommandsOop))) {
		fail("argument must be an Array");
		return null;
	}
	if (!((newMemSize > 0) && (newThreads > 0))) {
		fail("need memory and threads");
		return null;
	}
	if (newMemSize != memSize) {
		if (mem != null) {
			free (nile_shutdown (init));
		}
		threads = 0;
		memSize = newMemSize;
		mem = malloc(memSize);
		if (mem == null) {
			fail("buffer allocation failed");
			return null;
		}
	}
	if (threads != newThreads) {
		if (threads != 0) {
			nile_shutdown (init);
		}
		threads = newThreads;
		init = nile_startup (mem, memSize, threads);
		if (init == null) {
			threads = 0;
			fail("nile_startup failed");
			return null;
		}
	}
	reset();
	allCommands = interpreterProxy->firstIndexableField(allCommandsOop);
	allCommandsSize = interpreterProxy->slotSizeOf(allCommandsOop);
	for (i = 0; i <= (allCommandsSize - 1); i += 1) {
		errorItem = i + 1;
		eachCommandOop = allCommands[i];
		if (!(interpreterProxy->isArray(eachCommandOop))) {
			fail("Command must be an Array");
			return null;
		}
		wasSync = 0;
		executeCommand(eachCommandOop);
		if (interpreterProxy->failed()) {
			return null;
		}
		checkNileError();
		if (interpreterProxy->failed()) {
			return null;
		}
	}
	if (!(wasSync)) {
		errorItem += 1;
		executeSyncsize(null, 0);
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(3);
	return null;
}


/*	Answer number of (virtual) cores in this machine */

EXPORT(sqInt) primitiveNumberOfCores(void) {
	sqInt numCPU;
	sqInt _return_value;

	numCPU = sysconf( _SC_NPROCESSORS_ONLN );
	if (numCPU < 1) {
		fail("could not determine number of cores");
		return null;
	}
	_return_value = interpreterProxy->integerObjectOf(numCPU);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(1, _return_value);
	return null;
}

EXPORT(sqInt) primitiveTransformPoint(void) {
	float * matrix;
	sqInt aPoint;
	sqInt _return_value;
	sqInt matrix1;

	aPoint = interpreterProxy->stackValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	loadArgumentPoint(aPoint);
	/* begin loadArgumentMatrix: */
	matrix1 = interpreterProxy->stackObjectValue(1);
	if (interpreterProxy->failed()) {
		matrix = null;
		goto l1;
	}
	if (!((interpreterProxy->isWords(matrix1)) && ((interpreterProxy->slotSizeOf(matrix1)) == 6))) {
		interpreterProxy->primitiveFail();
		matrix = null;
		goto l1;
	}
	matrix = ((float *) (interpreterProxy->firstIndexableField(matrix1)));
l1:	/* end loadArgumentMatrix: */;
	if (interpreterProxy->failed()) {
		return null;
	}
	matrix2x3TransformPoint(matrix);
	_return_value = makePointand(m23ResultX, m23ResultY);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}

EXPORT(sqInt) primitiveTransformRectInto(void) {
	double  originY;
	double  maxX;
	double  originX;
	float * matrix;
	double  cornerY;
	double  cornerX;
	double  minY;
	double  maxY;
	double  minX;
	sqInt srcOop;
	sqInt dstOop;
	sqInt _return_value;
	sqInt matrix1;

	srcOop = interpreterProxy->stackValue(1);
	dstOop = interpreterProxy->stackValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	/* begin loadArgumentMatrix: */
	matrix1 = interpreterProxy->stackObjectValue(2);
	if (interpreterProxy->failed()) {
		matrix = null;
		goto l1;
	}
	if (!((interpreterProxy->isWords(matrix1)) && ((interpreterProxy->slotSizeOf(matrix1)) == 6))) {
		interpreterProxy->primitiveFail();
		matrix = null;
		goto l1;
	}
	matrix = ((float *) (interpreterProxy->firstIndexableField(matrix1)));
l1:	/* end loadArgumentMatrix: */;
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!((interpreterProxy->fetchClassOf(srcOop)) == (interpreterProxy->fetchClassOf(dstOop)))) {
		interpreterProxy->primitiveFail();
		return null;
	}
	if (!(interpreterProxy->isPointers(srcOop))) {
		interpreterProxy->primitiveFail();
		return null;
	}
	if (!((interpreterProxy->slotSizeOf(srcOop)) == 2)) {
		interpreterProxy->primitiveFail();
		return null;
	}
	loadArgumentPoint(interpreterProxy->fetchPointerofObject(0, srcOop));
	if (interpreterProxy->failed()) {
		return null;
	}
	originX = m23ArgX;
	originY = m23ArgY;
	matrix2x3TransformPoint(matrix);
	minX = (maxX = m23ResultX);

	/* Load bottom-right point */

	minY = (maxY = m23ResultY);
	loadArgumentPoint(interpreterProxy->fetchPointerofObject(1, srcOop));
	if (interpreterProxy->failed()) {
		return null;
	}
	cornerX = m23ArgX;
	cornerY = m23ArgY;
	matrix2x3TransformPoint(matrix);
	minX = ((minX < m23ResultX) ? minX : m23ResultX);
	maxX = ((maxX < m23ResultX) ? m23ResultX : maxX);
	minY = ((minY < m23ResultY) ? minY : m23ResultY);

	/* Load top-right point */

	maxY = ((maxY < m23ResultY) ? m23ResultY : maxY);
	m23ArgX = cornerX;
	m23ArgY = originY;
	matrix2x3TransformPoint(matrix);
	minX = ((minX < m23ResultX) ? minX : m23ResultX);
	maxX = ((maxX < m23ResultX) ? m23ResultX : maxX);
	minY = ((minY < m23ResultY) ? minY : m23ResultY);

	/* Load bottom-left point */

	maxY = ((maxY < m23ResultY) ? m23ResultY : maxY);
	m23ArgX = originX;
	m23ArgY = cornerY;
	matrix2x3TransformPoint(matrix);
	minX = ((minX < m23ResultX) ? minX : m23ResultX);
	maxX = ((maxX < m23ResultX) ? m23ResultX : maxX);
	minY = ((minY < m23ResultY) ? minY : m23ResultY);
	maxY = ((maxY < m23ResultY) ? m23ResultY : maxY);
	_return_value = storeRectanglex0y0x1y1(dstOop, minX, minY, maxX, maxY);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(3, _return_value);
	return null;
}

static sqInt reset(void) {
	sqInt i;

	stackP = 0;
	errorMsg = null;
	errorItem = 0;
	errorCode = NILE_STATUS_OK;
	i = 0;
	while ((i < ((sizeof(images)) / (sizeof(images[0])))) && (images[i].pixels != NULL)) {
		gezira_Image_done (&images[i]);
		images[i].pixels = NULL;
		i += 1;
	}
}


/*	Note: This is coded so that is can be run from Squeak. */

EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter) {
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = interpreterProxy->majorVersion() == VM_PROXY_MAJOR;
	if (ok == 0) {
		return 0;
	}
	ok = interpreterProxy->minorVersion() >= VM_PROXY_MINOR;
	return ok;
}

EXPORT(sqInt) shutdownModule(void) {
	if (!(mem == null)) {
		free (nile_shutdown (init));
		mem = null;
	}
	return 1;
}


/*	Check, round and store the result of a rectangle operation */

static sqInt storeRectanglex0y0x1y1(sqInt dstOop, double  x0, double  y0, double  x1, double  y1) {
	sqInt originOop;
	sqInt cornerOop;
	sqInt rectOop;

	interpreterProxy->pushRemappableOop(dstOop);
	originOop = makePointand(x0, y0);
	interpreterProxy->pushRemappableOop(originOop);
	cornerOop = makePointand(x1, y1);
	originOop = interpreterProxy->popRemappableOop();
	rectOop = interpreterProxy->popRemappableOop();
	interpreterProxy->storePointerofObjectwithValue(0, rectOop, originOop);
	interpreterProxy->storePointerofObjectwithValue(1, rectOop, cornerOop);
	return rectOop;
}


#ifdef SQUEAK_BUILTIN_PLUGIN


void* GeziraBindingsMT_exports[][3] = {
	{"GeziraBindingsMT", "shutdownModule", (void*)shutdownModule},
	{"GeziraBindingsMT", "primitiveTransformRectInto", (void*)primitiveTransformRectInto},
	{"GeziraBindingsMT", "primitiveExecuteThreadsMemCmds", (void*)primitiveExecuteThreadsMemCmds},
	{"GeziraBindingsMT", "primitiveTransformPoint", (void*)primitiveTransformPoint},
	{"GeziraBindingsMT", "primitiveNumberOfCores", (void*)primitiveNumberOfCores},
	{"GeziraBindingsMT", "primitiveErrorMessage", (void*)primitiveErrorMessage},
	{"GeziraBindingsMT", "initialiseModule", (void*)initialiseModule},
	{"GeziraBindingsMT", "primitiveErrorItem", (void*)primitiveErrorItem},
	{"GeziraBindingsMT", "setInterpreter", (void*)setInterpreter},
	{"GeziraBindingsMT", "getModuleName", (void*)getModuleName},
	{"GeziraBindingsMT", "primitiveErrorCode", (void*)primitiveErrorCode},
	{NULL, NULL, NULL}
};


#endif /* ifdef SQ_BUILTIN_PLUGIN */

