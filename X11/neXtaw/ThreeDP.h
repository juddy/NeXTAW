/*
* $KK: ThreeDP.h,v 0.3 92/11/04 xx:xx:xx keithley Exp $
*/
/* REMODIFIED FOR N*XTSTEP LOOK	 				*/
/* Modifications Copyright (c) 1996 by Alfredo Kojima		*/
/***********************************************************
Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.
Copyright 1992 by Kaleb Keithley

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital, MIT, or Kaleb
Keithley not be used in advertising or publicity pertaining to distribution 
of the software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef _ThreeDP_h
#define _ThreeDP_h

#include <X11/neXtaw/ThreeD.h>
#include <X11/neXtaw/SimpleP.h>

#define XtRRelief "Relief"
#define XtRBevel "Bevel"

typedef struct {
    Dimension	shadow_width;
    Pixel	top_shadow_pixel;
    Pixel	bot_shadow_pixel;
    Pixel	top_half_shadow_pixel;
    Pixel	bot_half_shadow_pixel;
    Pixmap	top_shadow_pxmap;
    Pixmap	bot_shadow_pxmap;
    Pixmap	top_half_shadow_pxmap;
    Pixmap	bot_half_shadow_pxmap;    
    int		top_shadow_contrast;
    int		bot_shadow_contrast;
    GC		top_shadow_GC;
    GC		bot_shadow_GC;
    GC		top_half_shadow_GC;
    GC		bot_half_shadow_GC;    
    XtPointer	user_data;
    Boolean	be_nice_to_cmap;
    XtRelief   	relief;
    XtBevel	bevel;
  } ThreeDPart;

/* Full instance record declaration */
typedef struct _ThreeDRec {
    CorePart	core;
    SimplePart	simple;
    ThreeDPart	threeD;
  } ThreeDRec;

typedef struct {
    void (*shadowdraw)();
  } ThreeDClassPart;

#define XtInheritXaw3dShadowDraw ((void (*)())_XtInherit)

/* Full class record declaration. */
typedef struct _ThreeDClassRec {
    CoreClassPart	core_class;
    SimpleClassPart	simple_class;
    ThreeDClassPart	threeD_class;
  } ThreeDClassRec;

/* Class pointer. */
extern ThreeDClassRec threeDClassRec;

#endif /* _ThreeDP_h */
