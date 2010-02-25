/* THE .H FILE */

#ifndef GEZIRA_H
#define GEZIRA_H

#include "nile.h"

typedef struct {
    nile_Kernel_t base;
} gezira_Sampler_t;

nile_Kernel_t *gezira_Sampler_clone(nile_t *nl, nile_Kernel_t *k_);

typedef struct {
    nile_Kernel_t base;
} gezira_Compositor_t;

nile_Kernel_t *gezira_Compositor_clone(nile_t *nl, nile_Kernel_t *k_);

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
} gezira_Canvas_t;

nile_Kernel_t *gezira_Canvas_clone(nile_t *nl, nile_Kernel_t *k_);

nile_Kernel_t *gezira_Canvas(nile_t *nl, 
                             nile_Kernel_t *k_ /* kargs */ , 
                             nile_Real_t v_start_x, 
                             nile_Real_t v_start_y);

nile_Kernel_t *gezira_CompositeSamplers(nile_t *nl /* kargs */ , 
                                        nile_Kernel_t *v_s1, 
                                        nile_Kernel_t *v_s2, 
                                        nile_Kernel_t *v_c);

static int gezira_CompositeSamplers_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_);

nile_Kernel_t *gezira_UniformColor(nile_t *nl /* kargs */ , 
                                   nile_Real_t v_c_a, 
                                   nile_Real_t v_c_r, 
                                   nile_Real_t v_c_g, 
                                   nile_Real_t v_c_b);

static int gezira_UniformColor_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeOver(nile_t *nl);

static int gezira_CompositeOver_process(nile_t *nl,
                                        nile_Kernel_t *k_,
                                        nile_Buffer_t **in_,
                                        nile_Buffer_t **out_);

nile_Kernel_t *gezira_FillBetweenEdges(nile_t *nl /* kargs */ , 
                                       nile_Real_t v_x0);

static int gezira_FillBetweenEdges_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_CreateSamplePoints(nile_t *nl /* kargs */ , 
                                         nile_Real_t v_start_x, 
                                         nile_Real_t v_start_y);

static int gezira_CreateSamplePoints_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_);

nile_Kernel_t *gezira_Render_(nile_t *nl /* kargs */ , 
                              nile_Kernel_t *v_s, 
                              nile_Kernel_t *v_c);

static int gezira_Render__process(nile_t *nl,
                                  nile_Kernel_t *k_,
                                  nile_Buffer_t **in_,
                                  nile_Buffer_t **out_);

nile_Kernel_t *gezira_Render(nile_t *nl /* kargs */ , 
                             nile_Kernel_t *v_s, 
                             nile_Kernel_t *v_c);

static int gezira_Render_process(nile_t *nl,
                                 nile_Kernel_t *k_,
                                 nile_Buffer_t **in_,
                                 nile_Buffer_t **out_);

nile_Kernel_t *gezira_TransformBeziers(nile_t *nl /* kargs */ , 
                                       nile_Real_t v_M_a, 
                                       nile_Real_t v_M_b, 
                                       nile_Real_t v_M_c, 
                                       nile_Real_t v_M_d, 
                                       nile_Real_t v_M_e, 
                                       nile_Real_t v_M_f);

static int gezira_TransformBeziers_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_ClipBeziers(nile_t *nl /* kargs */ , 
                                  nile_Real_t v_min_x, 
                                  nile_Real_t v_min_y, 
                                  nile_Real_t v_max_x, 
                                  nile_Real_t v_max_y);

static int gezira_ClipBeziers_process(nile_t *nl,
                                      nile_Kernel_t *k_,
                                      nile_Buffer_t **in_,
                                      nile_Buffer_t **out_);

nile_Kernel_t *gezira_DecomposeBeziers(nile_t *nl);

static int gezira_DecomposeBeziers_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeClear(nile_t *nl);

static int gezira_CompositeClear_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeSrc(nile_t *nl);

static int gezira_CompositeSrc_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeDst(nile_t *nl);

static int gezira_CompositeDst_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeDstOver(nile_t *nl);

static int gezira_CompositeDstOver_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeSrcIn(nile_t *nl);

static int gezira_CompositeSrcIn_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeDstIn(nile_t *nl);

static int gezira_CompositeDstIn_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeSrcOut(nile_t *nl);

static int gezira_CompositeSrcOut_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeDstOut(nile_t *nl);

static int gezira_CompositeDstOut_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeSrcAtop(nile_t *nl);

static int gezira_CompositeSrcAtop_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeDstAtop(nile_t *nl);

static int gezira_CompositeDstAtop_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeXor(nile_t *nl);

static int gezira_CompositeXor_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositePlus(nile_t *nl);

static int gezira_CompositePlus_process(nile_t *nl,
                                        nile_Kernel_t *k_,
                                        nile_Buffer_t **in_,
                                        nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeMultiply(nile_t *nl);

static int gezira_CompositeMultiply_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeScreen(nile_t *nl);

static int gezira_CompositeScreen_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeOverlay(nile_t *nl);

static int gezira_CompositeOverlay_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeDarken(nile_t *nl);

static int gezira_CompositeDarken_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeLighten(nile_t *nl);

static int gezira_CompositeLighten_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeColorDodge(nile_t *nl);

static int gezira_CompositeColorDodge_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeColorBurn(nile_t *nl);

static int gezira_CompositeColorBurn_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeHardLight(nile_t *nl);

static int gezira_CompositeHardLight_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeSoftLight(nile_t *nl);

static int gezira_CompositeSoftLight_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeDifference(nile_t *nl);

static int gezira_CompositeDifference_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeExclusion(nile_t *nl);

static int gezira_CompositeExclusion_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeSubtract(nile_t *nl);

static int gezira_CompositeSubtract_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_);

nile_Kernel_t *gezira_CompositeInvert(nile_t *nl);

static int gezira_CompositeInvert_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_);

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_o;
} gezira_StrokeJoin_t;

nile_Kernel_t *gezira_StrokeJoin_clone(nile_t *nl, nile_Kernel_t *k_);

nile_Kernel_t *gezira_StrokeJoin(nile_t *nl, 
                                 nile_Kernel_t *k_ /* kargs */ , 
                                 nile_Real_t v_o);

nile_Kernel_t *gezira_StrokeOffset(nile_t *nl /* kargs */ , 
                                   nile_Real_t v_o);

static int gezira_StrokeOffset_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_);

nile_Kernel_t *gezira_StrokeJoinMiter(nile_t *nl /* kargs */ , 
                                      nile_Real_t v_l, 
                                      nile_Real_t v_d);

static int gezira_StrokeJoinMiter_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_);

nile_Kernel_t *gezira_StrokeJoinRound(nile_t *nl /* kargs */ );

static int gezira_StrokeJoinRound_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_);

nile_Kernel_t *gezira_PrepareBeziersForStroke(nile_t *nl);

static int gezira_PrepareBeziersForStroke_process(nile_t *nl,
                                                  nile_Kernel_t *k_,
                                                  nile_Buffer_t **in_,
                                                  nile_Buffer_t **out_);

nile_Kernel_t *gezira_PrepareBeziersForOffset(nile_t *nl);

static int gezira_PrepareBeziersForOffset_process(nile_t *nl,
                                                  nile_Kernel_t *k_,
                                                  nile_Buffer_t **in_,
                                                  nile_Buffer_t **out_);

nile_Kernel_t *gezira_PrepareBeziersForJoin(nile_t *nl);

static int gezira_PrepareBeziersForJoin_process(nile_t *nl,
                                                nile_Kernel_t *k_,
                                                nile_Buffer_t **in_,
                                                nile_Buffer_t **out_);

nile_Kernel_t *gezira_PrepareBeziersForCap(nile_t *nl);

static int gezira_PrepareBeziersForCap_process(nile_t *nl,
                                               nile_Kernel_t *k_,
                                               nile_Buffer_t **in_,
                                               nile_Buffer_t **out_);

nile_Kernel_t *gezira_StrokeBeziers(nile_t *nl /* kargs */ , 
                                    nile_Real_t v_o, 
                                    nile_Kernel_t *v_j, 
                                    nile_Kernel_t *v_c);

static int gezira_StrokeBeziers_process(nile_t *nl,
                                        nile_Kernel_t *k_,
                                        nile_Buffer_t **in_,
                                        nile_Buffer_t **out_);

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_w;
    nile_Real_t v_h;
} gezira_ImageExtendMode_t;

nile_Kernel_t *gezira_ImageExtendMode_clone(nile_t *nl, nile_Kernel_t *k_);

nile_Kernel_t *gezira_ImageExtendMode(nile_t *nl, 
                                      nile_Kernel_t *k_ /* kargs */ , 
                                      nile_Real_t v_w, 
                                      nile_Real_t v_h);

typedef struct {
    nile_Kernel_t base;
} gezira_GradientShape_t;

nile_Kernel_t *gezira_GradientShape_clone(nile_t *nl, nile_Kernel_t *k_);

typedef struct {
    nile_Kernel_t base;
} gezira_GradientExtendMode_t;

nile_Kernel_t *gezira_GradientExtendMode_clone(nile_t *nl, nile_Kernel_t *k_);

typedef struct {
    nile_Kernel_t base;
} gezira_GradientColor_t;

nile_Kernel_t *gezira_GradientColor_clone(nile_t *nl, nile_Kernel_t *k_);

nile_Kernel_t *gezira_FilterBegin(nile_t *nl);

static int gezira_FilterBegin_process(nile_t *nl,
                                      nile_Kernel_t *k_,
                                      nile_Buffer_t **in_,
                                      nile_Buffer_t **out_);

nile_Kernel_t *gezira_FilterEnd(nile_t *nl);

static int gezira_FilterEnd_process(nile_t *nl,
                                    nile_Kernel_t *k_,
                                    nile_Buffer_t **in_,
                                    nile_Buffer_t **out_);

nile_Kernel_t *gezira_FilterSampler(nile_t *nl /* kargs */ , 
                                    nile_Kernel_t *v_s);

static int gezira_FilterSampler_process(nile_t *nl,
                                        nile_Kernel_t *k_,
                                        nile_Buffer_t **in_,
                                        nile_Buffer_t **out_);

nile_Kernel_t *gezira_TransformPoints(nile_t *nl /* kargs */ , 
                                      nile_Real_t v_M_a, 
                                      nile_Real_t v_M_b, 
                                      nile_Real_t v_M_c, 
                                      nile_Real_t v_M_d, 
                                      nile_Real_t v_M_e, 
                                      nile_Real_t v_M_f);

static int gezira_TransformPoints_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_);

nile_Kernel_t *gezira_GradientExtendPad(nile_t *nl);

static int gezira_GradientExtendPad_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_);

nile_Kernel_t *gezira_ImageExtendPad(nile_t *nl /* kargs */ , 
                                     nile_Real_t v_w, 
                                     nile_Real_t v_h);

static int gezira_ImageExtendPad_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_);

nile_Kernel_t *gezira_GradientExtendRepeat(nile_t *nl);

static int gezira_GradientExtendRepeat_process(nile_t *nl,
                                               nile_Kernel_t *k_,
                                               nile_Buffer_t **in_,
                                               nile_Buffer_t **out_);

nile_Kernel_t *gezira_ImageExtendRepeat(nile_t *nl /* kargs */ , 
                                        nile_Real_t v_w, 
                                        nile_Real_t v_h);

static int gezira_ImageExtendRepeat_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_);

nile_Kernel_t *gezira_GradientExtendReflect(nile_t *nl);

static int gezira_GradientExtendReflect_process(nile_t *nl,
                                                nile_Kernel_t *k_,
                                                nile_Buffer_t **in_,
                                                nile_Buffer_t **out_);

nile_Kernel_t *gezira_ImageExtendReflect(nile_t *nl /* kargs */ , 
                                         nile_Real_t v_w, 
                                         nile_Real_t v_h);

static int gezira_ImageExtendReflect_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_);

nile_Kernel_t *gezira_LinearGradientShape(nile_t *nl /* kargs */ , 
                                          nile_Real_t v_s00, 
                                          nile_Real_t v_dsdx, 
                                          nile_Real_t v_dsdy);

static int gezira_LinearGradientShape_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_);

nile_Kernel_t *gezira_RadialGradientShape(nile_t *nl /* kargs */ , 
                                          nile_Real_t v_C_x, 
                                          nile_Real_t v_C_y, 
                                          nile_Real_t v_r);

static int gezira_RadialGradientShape_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_);

nile_Kernel_t *gezira_GradientColorBegin(nile_t *nl);

static int gezira_GradientColorBegin_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_);

nile_Kernel_t *gezira_GradientColorSpan(nile_t *nl /* kargs */ , 
                                        nile_Real_t v_c0_a, 
                                        nile_Real_t v_c0_r, 
                                        nile_Real_t v_c0_g, 
                                        nile_Real_t v_c0_b, 
                                        nile_Real_t v_dcds_a, 
                                        nile_Real_t v_dcds_r, 
                                        nile_Real_t v_dcds_g, 
                                        nile_Real_t v_dcds_b, 
                                        nile_Real_t v_l);

static int gezira_GradientColorSpan_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_);

nile_Kernel_t *gezira_GradientColorEnd(nile_t *nl);

static int gezira_GradientColorEnd_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_);

nile_Kernel_t *gezira_Gradient(nile_t *nl /* kargs */ , 
                               nile_Kernel_t *v_s, 
                               nile_Kernel_t *v_e, 
                               nile_Kernel_t *v_c);

static int gezira_Gradient_process(nile_t *nl,
                                   nile_Kernel_t *k_,
                                   nile_Buffer_t **in_,
                                   nile_Buffer_t **out_);



#endif
