-- Preliminary version of 2D blending modes
-- jeff amelang
--
-- revisions:
-- 6/26/09 - creation


-- Sources: 
-- http://www.kaourantin.net/2005/09/some-word-on-blend-modes-in-flash.html
-- http://www.w3.org/TR/2003/WD-SVG12-20030715/#compositing
-- http://www.w3.org/TR/2004/WD-SVG12-20041027/rendering.html#compositing
-- http://livedocs.adobe.com/flash/9.0/UsingFlash/help.html?content=WSd60f23110762d6b883b18f10cb1fe1af6-7d5b.html
-- http://livedocs.adobe.com/flash/9.0/UsingFlash/help.html?content=WSd60f23110762d6b883b18f10cb1fe1af6-7d5b.html
-- http://www.pegtop.net/delphi/articles/blendmodes/
-- http://www.w3.org/TR/SVG/filters.html#feBlend
-- 

-- Porter-Duff Blending Modes

-- A = Source (Thing to put on Background)
-- B = Destination (Background)

CompositeClear : Compositor
    \forall [S, D]
    >> 0

CompositeSrc : Compositor
    \forall [S, D]
    >> S

CompositeDst : Compositor
    \forall [S, D]
    >> D

CompositeSrcOver : Compositor
    \forall [S, D]
    >> S + D * (1 - S.a)

CompositeDstOver : Compositor
    \forall [S, D]
    >> D + S * (1 - D.a)

CompositeSrcIn : Compositor
    \forall [S, D]
    >> S * D.a

CompositeDstIn : Compositor
    \forall [S, D]
    >> D * S.a

CompositeSrcOut : Compositor
    \forall [S, D]
    >> S * (1 - D.a)

CompositeDstOut : Compositor
    \forall [S, D]
    >> D * (1 - S.a)

CompositeSrcAtop : Compositor
    \forall [S, D]
    >> S * D.a + D * (1 - S.a)

CompositeDstAtop : Compositor
    \forall [S, D]
    >> D * S.a + S * (1 - D.a)

CompositeXor : Compositor
    \forall [S, D]
    >> S * (1 - D.a) + D * (1 - S.a)



-- SVG Composite Modes

CompositePlus : Compositor
    \forall [S, D}
    >> S + D

CompositeMultiply : Compositor
    \forall [S, D}
    >> S * D + S * (1 - D.a) + D * (1 - S.a)

CompositeScreen : Compositor
    \forall [S, D}
    >> S + D - S * D

CompositeOverlay : Compositor
    \forall [S, D}
    C1 <- S.a*D.a - 2*(D.a - D)*(S.a - S) + S*(1 - D.a) + D*(1 - S.a) 
    C2 <- 2*S*D + S*(1 - D.a) + D*(1 - S.a)
    >> C1 ?2*D<D.a? C2

CompositeDarken : Compositor
    \forall [S, D}
    >> S*D.a \min D*S.a + S * (1 - D.a) + D * (1 - S.a)

CompositeLighten : Compositor
    \forall [S, D}
    >> S*D.a \max D*S.a + S * (1 - D.a) + D * (1 - S.a)

CompositeColorDodge : Compositor
    \forall [S, D}
    C1 <- D * S.a / (1 - S/S.a) + S * (1 - D.a) + D * (1 - S.a) \min 1
    C2 <- S.a * D.a + S * (1 - D.a) + D (1 - S.a)
    >> C1 ?S*D.a+D*S.a>=S.a*D.a? C2

CompositeColorBurn : Compositor
    \forall [S, D}
    C1 <- S.a * (S*D.a + D*S.a - S.a*D.a)/S + S*(1 - D.a) + D*(1 - S.a)
    C2 <- S*(1 - D.a) + D*(1 - S.a)
    >> C1 ?S*D.a+D*S.a<=S.a*D.a? C2

CompositeHardLight : Compositor
    \forall [S, D}
    C1 <- S.a*D.a - 2*(D.a - D)*(S.a - S) + S*(1 - D.a) + D*(1 - S.a)
    C2 <- 2*S*D + S*(1 - D.a) + D*(1 - S.a)
    >> C1 ?2*S<S.a? C2

CompositeSoftLight : Compositor
    \forall [S, D}
    C0 <- S*(1 - D.a) + D*(1 - S.a)
    C1 <- D*(S.a - (1 - D/D.a)*(2*S - S.a)) + C0
    C2 <- D*(S.a - (1 - D/D.a)*(2*S - S.a)*(3 - 8*D/D.a)) + C0
    C3 <- (D*S.a + ((D/D.a)^0.5*D.a - D)*(2*S - S.a)) + C0
    >> C3 ?D*8<=D.a? C2 ?2*S<S.a? C1

CompositeDifference : Compositor
    \forall [S, D}
    C <- S + D - 2 * S*D.a \min D*S.a
    >> [C.a + S.a * D.a, *C.rgb]

CompositeExclusion : Compositor
    \forall [S, D}
    C <- (S*D.a + D*S.a - 2*S*D) + S*(1 - D.a) + D*(1 - S.a)
    >> [C.a + S.a * D.a, *C.rgb]

-- Adobe Flash modes
--
-- Normal - Same as CompositeSrcOver
-- Layer - Same as Normal?  
-- Darken - Same as CompositeDarken
-- Multiply - Same as CompositeMultiply
-- Lighten - Same as CompositeLighten
-- Screen - Same as CompositeScreen
-- Overlay - Same as CompositeOverlay
-- Hard Light - Same as CompositeHardLight
-- Difference - Same as CompositeDifference
--
-- Add 
CompositeAdd : Compositor
    \forall [S, D}
    >> S + D \min 1
-- Subtract 
CompositeSubtract : Compositor
    \forall [S, D}
    >> S + D - 1 \max 0
-- Invert 
CompositeInvert : Compositor
    \forall [S, D}
    >> 1 - D
