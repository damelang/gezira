#ifndef GEZIRA_H
#define GEZIRA_H

#include "nile.h"

nile_Process_t *
gezira_TransformPoints (nile_Process_t *p, 
                        float v_M_a, 
                        float v_M_b, 
                        float v_M_c, 
                        float v_M_d, 
                        float v_M_e, 
                        float v_M_f);

nile_Process_t *
gezira_TransformBeziers (nile_Process_t *p, 
                         float v_M_a, 
                         float v_M_b, 
                         float v_M_c, 
                         float v_M_d, 
                         float v_M_e, 
                         float v_M_f);

nile_Process_t *
gezira_UniformColor (nile_Process_t *p, 
                     float v_C_a, 
                     float v_C_r, 
                     float v_C_g, 
                     float v_C_b);

nile_Process_t *
gezira_CompositeTextures (nile_Process_t *p, 
                          nile_Process_t *v_t1, 
                          nile_Process_t *v_t2, 
                          nile_Process_t *v_c);

nile_Process_t *
gezira_CalculateBounds (nile_Process_t *p);

nile_Process_t *
gezira_ClipBeziers (nile_Process_t *p, 
                    float v_min_x, 
                    float v_min_y, 
                    float v_max_x, 
                    float v_max_y);

nile_Process_t *
gezira_CompositeClear (nile_Process_t *p);

nile_Process_t *
gezira_CompositeSrc (nile_Process_t *p);

nile_Process_t *
gezira_CompositeDst (nile_Process_t *p);

nile_Process_t *
gezira_CompositeOver (nile_Process_t *p);

nile_Process_t *
gezira_CompositeDstOver (nile_Process_t *p);

nile_Process_t *
gezira_CompositeSrcIn (nile_Process_t *p);

nile_Process_t *
gezira_CompositeDstIn (nile_Process_t *p);

nile_Process_t *
gezira_CompositeSrcOut (nile_Process_t *p);

nile_Process_t *
gezira_CompositeDstOut (nile_Process_t *p);

nile_Process_t *
gezira_CompositeSrcAtop (nile_Process_t *p);

nile_Process_t *
gezira_CompositeDstAtop (nile_Process_t *p);

nile_Process_t *
gezira_CompositeXor (nile_Process_t *p);

nile_Process_t *
gezira_CompositePlus (nile_Process_t *p);

nile_Process_t *
gezira_CompositeMultiply (nile_Process_t *p);

nile_Process_t *
gezira_CompositeScreen (nile_Process_t *p);

nile_Process_t *
gezira_CompositeOverlay (nile_Process_t *p);

nile_Process_t *
gezira_CompositeDarken (nile_Process_t *p);

nile_Process_t *
gezira_CompositeLighten (nile_Process_t *p);

nile_Process_t *
gezira_CompositeColorDodge (nile_Process_t *p);

nile_Process_t *
gezira_CompositeColorBurn (nile_Process_t *p);

nile_Process_t *
gezira_CompositeHardLight (nile_Process_t *p);

nile_Process_t *
gezira_CompositeSoftLight (nile_Process_t *p);

nile_Process_t *
gezira_CompositeDifference (nile_Process_t *p);

nile_Process_t *
gezira_CompositeExclusion (nile_Process_t *p);

nile_Process_t *
gezira_CompositeSubtract (nile_Process_t *p);

nile_Process_t *
gezira_CompositeInvert (nile_Process_t *p);

nile_Process_t *
gezira_InverseOver (nile_Process_t *p, 
                    float v_a);

nile_Process_t *
gezira_ContrastiveOver (nile_Process_t *p, 
                        float v_a);

nile_Process_t *
gezira_SumWeightedColors (nile_Process_t *p, 
                          float v_n);

nile_Process_t *
gezira_BilinearFilterPoints (nile_Process_t *p);

nile_Process_t *
gezira_BilinearFilterWeights (nile_Process_t *p);

nile_Process_t *
gezira_BilinearFilter (nile_Process_t *p, 
                       nile_Process_t *v_t);

nile_Process_t *
gezira_BicubicFilterPoints (nile_Process_t *p);

nile_Process_t *
gezira_BicubicFilterDeltas (nile_Process_t *p);

nile_Process_t *
gezira_BicubicFilterWeights (nile_Process_t *p);

nile_Process_t *
gezira_BicubicFilter (nile_Process_t *p, 
                      nile_Process_t *v_t);

nile_Process_t *
gezira_GaussianBlur5x1Points (nile_Process_t *p);

nile_Process_t *
gezira_GaussianBlur1x5Points (nile_Process_t *p);

nile_Process_t *
gezira_GaussianBlur5x1Weights (nile_Process_t *p, 
                               float v_f);

nile_Process_t *
gezira_GaussianBlur5x1 (nile_Process_t *p, 
                        float v_f, 
                        nile_Process_t *v_t);

nile_Process_t *
gezira_GaussianBlur1x5 (nile_Process_t *p, 
                        float v_f, 
                        nile_Process_t *v_t);

nile_Process_t *
gezira_GaussianBlur11x1Points (nile_Process_t *p);

nile_Process_t *
gezira_GaussianBlur1x11Points (nile_Process_t *p);

nile_Process_t *
gezira_GaussianBlur11x1Weights (nile_Process_t *p, 
                                float v_f);

nile_Process_t *
gezira_GaussianBlur11x1 (nile_Process_t *p, 
                         float v_f, 
                         nile_Process_t *v_t);

nile_Process_t *
gezira_GaussianBlur1x11 (nile_Process_t *p, 
                         float v_f, 
                         nile_Process_t *v_t);

nile_Process_t *
gezira_GaussianBlur21x1Points (nile_Process_t *p);

nile_Process_t *
gezira_GaussianBlur1x21Points (nile_Process_t *p);

nile_Process_t *
gezira_GaussianBlur21x1Weights (nile_Process_t *p, 
                                float v_f);

nile_Process_t *
gezira_GaussianBlur21x1 (nile_Process_t *p, 
                         float v_f, 
                         nile_Process_t *v_t);

nile_Process_t *
gezira_GaussianBlur1x21 (nile_Process_t *p, 
                         float v_f, 
                         nile_Process_t *v_t);

nile_Process_t *
gezira_LinearGradientShape (nile_Process_t *p, 
                            float v_s00, 
                            float v_dsdx, 
                            float v_dsdy);

nile_Process_t *
gezira_RadialGradientShape (nile_Process_t *p, 
                            float v_C_x, 
                            float v_C_y, 
                            float v_r);

nile_Process_t *
gezira_GradientExtendPad (nile_Process_t *p);

nile_Process_t *
gezira_GradientExtendRepeat (nile_Process_t *p);

nile_Process_t *
gezira_GradientExtendReflect (nile_Process_t *p);

nile_Process_t *
gezira_GradientColorBegin (nile_Process_t *p);

nile_Process_t *
gezira_GradientColorSpan (nile_Process_t *p, 
                          float v_c0_a, 
                          float v_c0_r, 
                          float v_c0_g, 
                          float v_c0_b, 
                          float v_dcds_a, 
                          float v_dcds_r, 
                          float v_dcds_g, 
                          float v_dcds_b, 
                          float v_l);

nile_Process_t *
gezira_GradientColorEnd (nile_Process_t *p);

nile_Process_t *
gezira_Gradient (nile_Process_t *p, 
                 nile_Process_t *v_s, 
                 nile_Process_t *v_m, 
                 nile_Process_t *v_c);

nile_Process_t *
gezira_ImageExtendPad (nile_Process_t *p, 
                       float v_D_x, 
                       float v_D_y);

nile_Process_t *
gezira_ImageExtendRepeat (nile_Process_t *p, 
                          float v_D_x, 
                          float v_D_y);

nile_Process_t *
gezira_ImageExtendReflect (nile_Process_t *p, 
                           float v_D_x, 
                           float v_D_y);

nile_Process_t *
gezira_DecomposeBeziers (nile_Process_t *p);

nile_Process_t *
gezira_CombineEdgeSamples (nile_Process_t *p);

nile_Process_t *
gezira_Rasterize (nile_Process_t *p);

nile_Process_t *
gezira_ExpandSpans (nile_Process_t *p);

nile_Process_t *
gezira_ExtractSamplePoints (nile_Process_t *p);

nile_Process_t *
gezira_ApplyTexture (nile_Process_t *p, 
                     nile_Process_t *v_t);



#endif

