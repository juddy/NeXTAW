/*
* $KK: ThreeD.c,v 0.3 92/11/04 xx:xx:xx keithley Exp $ 
*/
/* MODIFIED FOR N*XTSTEP LOOK	 				*/
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

#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/IntrinsicP.h>
#include "XawInit.h"
#include "ThreeDP.h"
#include <X11/Xosdefs.h>
#include <X11/Xmu/Xmu.h>

/* Initialization of defaults */

#define XtNtopShadowPixmap "topShadowPixmap"
#define XtCTopShadowPixmap "TopShadowPixmap"
#define XtNbottomShadowPixmap "bottomShadowPixmap"
#define XtCBottomShadowPixmap "BottomShadowPixmap"

#define offset(field) XtOffsetOf(ThreeDRec, field)

static XtRelief defRelief = XtReliefRaised;
static XtBevel defBevel = XtBevelRounded;

static XtResource resources[] = {
    {XtNshadowWidth, XtCShadowWidth, XtRDimension, sizeof(Dimension),
	offset(threeD.shadow_width), XtRImmediate, (XtPointer) 2},
    {XtNtopShadowPixel, XtCTopShadowPixel, XtRPixel, sizeof(Pixel),
	offset(threeD.top_shadow_pixel), XtRString, XtDefaultForeground},
    {XtNbottomShadowPixel, XtCBottomShadowPixel, XtRPixel, sizeof(Pixel),
	offset(threeD.bot_shadow_pixel), XtRString, XtDefaultForeground},
    {XtNtopShadowPixmap, XtCTopShadowPixmap, XtRPixmap, sizeof(Pixmap),
	offset(threeD.top_shadow_pxmap), XtRImmediate, (XtPointer) NULL},
    {XtNbottomShadowPixmap, XtCBottomShadowPixmap, XtRPixmap, sizeof(Pixmap),
	offset(threeD.bot_shadow_pxmap), XtRImmediate, (XtPointer) NULL},
#if 0	/* top shadow is the same colour as the background */
    {XtNtopShadowContrast, XtCTopShadowContrast, XtRInt, sizeof(int),
	offset(threeD.top_shadow_contrast), XtRImmediate, (XtPointer) 0},
    {XtNbottomShadowContrast, XtCBottomShadowContrast, XtRInt, sizeof(int),
	offset(threeD.bot_shadow_contrast), XtRImmediate, (XtPointer) 50},
#else	/* top shadow is slightly lighter than the background */
    {XtNtopShadowContrast, XtCTopShadowContrast, XtRInt, sizeof(int),
	offset(threeD.top_shadow_contrast), XtRImmediate, (XtPointer) 20},
    {XtNbottomShadowContrast, XtCBottomShadowContrast, XtRInt, sizeof(int),
	offset(threeD.bot_shadow_contrast), XtRImmediate, (XtPointer) 40},
#endif
    {XtNuserData, XtCUserData, XtRPointer, sizeof(XtPointer),
	offset(threeD.user_data), XtRPointer, (XtPointer) NULL},
    {XtNbeNiceToColormap, XtCBeNiceToColormap, XtRBoolean, sizeof(Boolean),
	offset(threeD.be_nice_to_cmap), XtRImmediate, (XtPointer) False},
    {XtNborderWidth, XtCBorderWidth, XtRDimension, sizeof(Dimension),
	XtOffsetOf(RectObjRec,rectangle.border_width), XtRImmediate,
	(XtPointer)0},
    {XtNrelief, XtCRelief, XtRRelief, sizeof(XtRelief),
	offset(threeD.relief), XtRRelief, (XtPointer) &defRelief},
    {XtNbevel, XtCBevel, XtRBevel, sizeof(XtBevel),
	offset(threeD.bevel), XtRBevel, (XtPointer) &defBevel},
};

#undef offset

static void ClassInitialize(), ClassPartInitialize(), Initialize(), Destroy();
static void Redisplay(), Realize(), _Xaw3dDrawShadows();
static Boolean SetValues();
static void Draw3DFrame();

ThreeDClassRec threeDClassRec = {
    { /* core fields */
    /* superclass		*/	(WidgetClass) &simpleClassRec,
    /* class_name		*/	"ThreeD",
    /* widget_size		*/	sizeof(ThreeDRec),
    /* class_initialize		*/	ClassInitialize,
    /* class_part_initialize	*/	ClassPartInitialize,
    /* class_inited		*/	FALSE,
    /* initialize		*/	Initialize,
    /* initialize_hook		*/	NULL,
    /* realize			*/	Realize,
    /* actions			*/	NULL,
    /* num_actions		*/	0,
    /* resources		*/	resources,
    /* resource_count		*/	XtNumber(resources),
    /* xrm_class		*/	NULLQUARK,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	TRUE,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	Destroy,
    /* resize			*/	XtInheritResize,
    /* expose			*/	Redisplay,
    /* set_values		*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	NULL,
    /* query_geometry           */	XtInheritQueryGeometry,
    /* display_accelerator      */	XtInheritDisplayAccelerator,
    /* extension                */	NULL
    },
    { /* simple fields */
    /* change_sensitive         */      XtInheritChangeSensitive
    },
    { /* threeD fields */
    /* shadow draw              */      _Xaw3dDrawShadows
    }
};

WidgetClass threeDWidgetClass = (WidgetClass) &threeDClassRec;

/****************************************************************
 *
 * Private Procedures
 *
 ****************************************************************/

#define mbshadowpm_size 3
static char mbshadowpm_bits[] = {0x05, 0x03, 0x06};

#define mtshadowpm_size 3
static char mtshadowpm_bits[] = {0x02, 0x04, 0x01};

#define shadowpm_size 2
static char shadowpm_bits[] = {0x02, 0x01};


#ifdef USEGRAY
#include <stdio.h>
unsigned long grayPixel(dpy, scn)
Display *dpy;
Screen	*scn;
    {
    static XColor Gray = 
    {
	/* pixel */            0, 
	/* red, green, blue */ 0,0,0, 
        /* flags */            0,
        /* pad */              0
    };
    if (!Gray.pixel)
	{
	XColor exact;
	(void) XAllocNamedColor(dpy, DefaultColormapOfScreen (scn), 
				"gray", &Gray,&exact);  /* Blindflug */
	}
    return Gray.pixel;
    }
#define setPixel(p,dpy,scn) grayPixel(dpy,scn)
#else
#define setPixel(p,dpy,scn) (p)
#endif


/* ARGSUSED */
static void AllocTopShadowGC (w)
    Widget w;
{
    ThreeDWidget	tdw = (ThreeDWidget) w;
    Screen		*scn = XtScreen (w);
    XtGCMask		valuemask;
    XGCValues		myXGCV;

    if (tdw->threeD.be_nice_to_cmap || DefaultDepthOfScreen (scn) == 1) {
	valuemask = GCTile | GCFillStyle;
	myXGCV.tile = tdw->threeD.top_shadow_pxmap;
	myXGCV.fill_style = FillTiled;
    } else {
	valuemask = GCForeground;
	myXGCV.foreground = tdw->threeD.top_shadow_pixel;
    }
    tdw->threeD.top_shadow_GC = XtGetGC(w, valuemask, &myXGCV);
    if (tdw->threeD.be_nice_to_cmap || DefaultDepthOfScreen (scn) == 1) {
	valuemask = GCTile | GCFillStyle;
	myXGCV.tile = tdw->threeD.top_half_shadow_pxmap;
	myXGCV.fill_style = FillTiled;
    } else {
	valuemask = GCForeground;
	myXGCV.foreground = tdw->threeD.top_half_shadow_pixel;
    }
    tdw->threeD.top_half_shadow_GC = XtGetGC(w, valuemask, &myXGCV);
}

/* ARGSUSED */
static void AllocBotShadowGC (w)
    Widget w;
{
    ThreeDWidget	tdw = (ThreeDWidget) w;
    Screen		*scn = XtScreen (w);
    XtGCMask		valuemask;
    XGCValues		myXGCV;

    if (tdw->threeD.be_nice_to_cmap || DefaultDepthOfScreen (scn) == 1) {
	valuemask = GCTile | GCFillStyle;
	myXGCV.tile = tdw->threeD.bot_shadow_pxmap;
	myXGCV.fill_style = FillTiled;
    } else {
	valuemask = GCForeground;
	myXGCV.foreground = tdw->threeD.bot_shadow_pixel;
    }
    tdw->threeD.bot_shadow_GC = XtGetGC(w, valuemask, &myXGCV);
    if (tdw->threeD.be_nice_to_cmap || DefaultDepthOfScreen (scn) == 1) {
	valuemask = GCTile | GCFillStyle;
	myXGCV.tile = tdw->threeD.bot_half_shadow_pxmap;
	myXGCV.fill_style = FillTiled;
    } else {
	valuemask = GCForeground|GCBackground;
	myXGCV.background = tdw->threeD.bot_half_shadow_pixel;
	myXGCV.foreground = tdw->threeD.bot_half_shadow_pixel;
    }
    tdw->threeD.bot_half_shadow_GC = XtGetGC(w, valuemask, &myXGCV);   
}

/* ARGSUSED */
static void AllocTopShadowPixmap (new)
    Widget new;
{
    ThreeDWidget	tdw = (ThreeDWidget) new;
    Display		*dpy = XtDisplay (new);
    Screen		*scn = XtScreen (new);
    unsigned long	top_fg_pixel = 0, top_bg_pixel = 0;
    unsigned long	top_half_fg_pixel = 0, top_half_bg_pixel = 0;
    char		*pm_data = NULL;
    Boolean		create_pixmap = FALSE;
    unsigned int        pm_size;

    /*
     * I know, we're going to create two pixmaps for each and every
     * shadow'd widget.  Yeuck.  I'm semi-relying on server side
     * pixmap cacheing.
     */

    if (DefaultDepthOfScreen (scn) == 1) {
	top_fg_pixel = top_half_fg_pixel = BlackPixelOfScreen (scn);
	top_bg_pixel = top_half_bg_pixel = WhitePixelOfScreen (scn);
	pm_data = mtshadowpm_bits;
        pm_size = mtshadowpm_size;
	create_pixmap = TRUE;
    } else if (tdw->threeD.be_nice_to_cmap) {
	if (tdw->core.background_pixel == WhitePixelOfScreen (scn)) {
	    top_bg_pixel = WhitePixelOfScreen (scn);
	    top_fg_pixel = BlackPixelOfScreen (scn);
	    top_half_bg_pixel = BlackPixelOfScreen (scn);
	    top_half_fg_pixel = setPixel( WhitePixelOfScreen (scn), dpy, scn);
	} else if (tdw->core.background_pixel == BlackPixelOfScreen (scn)) {
	    top_fg_pixel = BlackPixelOfScreen (scn);
	    top_bg_pixel = WhitePixelOfScreen (scn);
            top_half_bg_pixel = BlackPixelOfScreen (scn);
            top_half_fg_pixel = setPixel( WhitePixelOfScreen (scn), dpy, scn);
	} else {
	    top_bg_pixel = top_fg_pixel = tdw->core.background_pixel;
	    top_half_fg_pixel = top_half_bg_pixel = WhitePixelOfScreen (scn);
	}
#ifndef USEGRAY
	if (tdw->core.background_pixel == WhitePixelOfScreen (scn) ||
	    tdw->core.background_pixel == BlackPixelOfScreen (scn)) {
	    pm_data = mtshadowpm_bits;
       	    pm_size = mtshadowpm_size;
       } else 
#endif
       {
       	    pm_data = shadowpm_bits;
            pm_size = shadowpm_size;
       }
	
	create_pixmap = TRUE;
    } else {
	pm_size = 0; /* keep gcc happy */
    }

    if (create_pixmap) {
	tdw->threeD.top_shadow_pxmap = XCreatePixmapFromBitmapData (dpy,
			RootWindowOfScreen (scn),
			pm_data,
			pm_size,
			pm_size,
			top_fg_pixel,
			top_bg_pixel,
			DefaultDepthOfScreen (scn));
	tdw->threeD.top_half_shadow_pxmap = XCreatePixmapFromBitmapData (dpy,
			RootWindowOfScreen (scn),
			pm_data,
			pm_size,
			pm_size,
			top_half_fg_pixel,
			top_half_bg_pixel,
			DefaultDepthOfScreen (scn));
    }
}

/* ARGSUSED */
static void AllocBotShadowPixmap (new)
    Widget new;
{
    ThreeDWidget	tdw = (ThreeDWidget) new;
    Display		*dpy = XtDisplay (new);
    Screen		*scn = XtScreen (new);
    unsigned long	bot_fg_pixel = 0, bot_bg_pixel = 0;
    unsigned long	bot_half_fg_pixel = 0, bot_half_bg_pixel = 0;    
    char		*pm_data = NULL;
    Boolean		create_pixmap = FALSE;
    unsigned int        pm_size;

    if (DefaultDepthOfScreen (scn) == 1) {
	bot_half_fg_pixel = bot_fg_pixel = BlackPixelOfScreen (scn);
	bot_half_bg_pixel = bot_bg_pixel = WhitePixelOfScreen (scn);
	pm_data = mbshadowpm_bits;
        pm_size = mbshadowpm_size;
	create_pixmap = TRUE;
    } else if (tdw->threeD.be_nice_to_cmap) {
	if (tdw->core.background_pixel == WhitePixelOfScreen (scn)) {
	    bot_fg_pixel = WhitePixelOfScreen (scn);
	    bot_half_fg_pixel = 
		bot_bg_pixel = setPixel( BlackPixelOfScreen (scn), dpy, scn);
	    bot_half_bg_pixel = BlackPixelOfScreen (scn);
	} else if (tdw->core.background_pixel == BlackPixelOfScreen (scn)) {
	    bot_half_bg_pixel = 
	        bot_fg_pixel = setPixel( BlackPixelOfScreen (scn), dpy, scn);
	    bot_half_fg_pixel = bot_bg_pixel = BlackPixelOfScreen (scn);
	} else {
	    bot_fg_pixel = tdw->core.background_pixel;
	    bot_half_bg_pixel = 
	        bot_half_fg_pixel = bot_bg_pixel = BlackPixelOfScreen (scn);
	}
#ifndef USEGRAY
	if (tdw->core.background_pixel == WhitePixelOfScreen (scn) ||
	    tdw->core.background_pixel == BlackPixelOfScreen (scn)) {
	    pm_data = mbshadowpm_bits;
	    pm_size = mbshadowpm_size;
	} else 
#endif
        {
	    pm_data = shadowpm_bits;
	    pm_size = shadowpm_size;
        }
	create_pixmap = TRUE;
    } else {
	pm_size = 0; /* keep gcc happy */
    }
    if (create_pixmap) {
	tdw->threeD.bot_shadow_pxmap = XCreatePixmapFromBitmapData (dpy,
			RootWindowOfScreen (scn),
			pm_data,
			pm_size,
			pm_size,
			bot_fg_pixel,
			bot_bg_pixel,
			DefaultDepthOfScreen (scn));
	tdw->threeD.bot_half_shadow_pxmap = XCreatePixmapFromBitmapData (dpy,
			RootWindowOfScreen (scn),
			pm_data,
			pm_size,
			pm_size,
			bot_half_fg_pixel,
			bot_half_bg_pixel,
			DefaultDepthOfScreen (scn));
    }
}

/* ARGSUSED */
void Xaw3dComputeTopShadowRGB (new, xcol_out)
    Widget new;
    XColor *xcol_out;
{
    if (XtIsSubclass (new, threeDWidgetClass)) {
	ThreeDWidget tdw = (ThreeDWidget) new;
	XColor get_c;
	double contrast;
	Display *dpy = XtDisplay (new);
	Screen *scn = XtScreen (new);
	Colormap cmap = DefaultColormapOfScreen (scn);

	get_c.pixel = tdw->core.background_pixel;
	if (get_c.pixel == WhitePixelOfScreen (scn) ||
	    get_c.pixel == BlackPixelOfScreen (scn)) {
	    contrast = (100 - tdw->threeD.top_shadow_contrast) / 100.0;
	    xcol_out->red   = contrast * 65535.0;
	    xcol_out->green = contrast * 65535.0;
	    xcol_out->blue  = contrast * 65535.0;
	} else {
	    contrast = 1.0 + tdw->threeD.top_shadow_contrast / 100.0;
	    XQueryColor (dpy, cmap, &get_c);
#define MIN(x,y) (unsigned short) (x < y) ? x : y
	    xcol_out->red   = MIN (65535, (int) (contrast * (double) get_c.red));
	    xcol_out->green = MIN (65535, (int) (contrast * (double) get_c.green));
	    xcol_out->blue  = MIN (65535, (int) (contrast * (double) get_c.blue));
#undef MIN
	}
    } else
	xcol_out->red = xcol_out->green = xcol_out->blue = 0;
}

/* ARGSUSED */
static void AllocTopShadowPixel (new)
    Widget new;
{
    XColor set_c;
    ThreeDWidget tdw = (ThreeDWidget) new;
    Display *dpy = XtDisplay (new);
    Screen *scn = XtScreen (new);
    Colormap cmap = DefaultColormapOfScreen (scn);

    Xaw3dComputeTopShadowRGB (new, &set_c);
    (void) XAllocColor (dpy, cmap, &set_c);
    tdw->threeD.top_shadow_pixel = set_c.pixel;
    tdw->threeD.top_half_shadow_pixel = WhitePixelOfScreen (scn);
}

/* ARGSUSED */
void Xaw3dComputeBottomShadowRGB (new, xcol_out)
    Widget new;
    XColor *xcol_out;
{
    if (XtIsSubclass (new, threeDWidgetClass)) {
	ThreeDWidget tdw = (ThreeDWidget) new;
	XColor get_c;
	double contrast;
	Display *dpy = XtDisplay (new);
	Screen *scn = XtScreen (new);
	Colormap cmap = DefaultColormapOfScreen (scn);

	get_c.pixel = tdw->core.background_pixel;
	if (get_c.pixel == WhitePixelOfScreen (scn) ||
	    get_c.pixel == BlackPixelOfScreen (scn)) {
	    contrast = tdw->threeD.bot_shadow_contrast / 100.0;
	    xcol_out->red   = contrast * 65535.0;
	    xcol_out->green = contrast * 65535.0;
	    xcol_out->blue  = contrast * 65535.0;
	} else {
	    XQueryColor (dpy, cmap, &get_c);
	    contrast = (100 - tdw->threeD.bot_shadow_contrast) / 100.0;
	    xcol_out->red   = contrast * get_c.red;
	    xcol_out->green = contrast * get_c.green;
	    xcol_out->blue  = contrast * get_c.blue;
	}
    } else
	xcol_out->red = xcol_out->green = xcol_out->blue = 0;
}

/* ARGSUSED */
static void AllocBotShadowPixel (new)
    Widget new;
{
    XColor set_c;
    ThreeDWidget tdw = (ThreeDWidget) new;
    Display *dpy = XtDisplay (new);
    Screen *scn = XtScreen (new);
    Colormap cmap = DefaultColormapOfScreen (scn);

    Xaw3dComputeBottomShadowRGB (new, &set_c);
    (void) XAllocColor (dpy, cmap, &set_c);
    tdw->threeD.bot_shadow_pixel = set_c.pixel;
    tdw->threeD.bot_half_shadow_pixel = BlackPixelOfScreen(scn);
}    


static XrmQuark	XtQReliefSimple, XtQReliefSunken, XtQReliefFlat,
		XtQReliefRaised, XtQReliefGroove, XtQReliefRidge;

static XrmQuark XtQBevelRounded, XtQBevelSolid;

#define	done(address, type) \
	{ toVal->size = sizeof(type); \
	  toVal->addr = (XPointer) address; \
	  return; \
	}

/* ARGSUSED */
/* FIXME: This function looks broken. It returns e.g. XtQReliefSimple
   when XtReliefSimple seems more reasonable.
*/
static void _CvtStringToRelief(args, num_args, fromVal, toVal)
    XrmValuePtr args;		/* unused */
    Cardinal    *num_args;      /* unused */
    XrmValuePtr fromVal;
    XrmValuePtr toVal;
{
    static XtRelief relief;
    XrmQuark q;
    char lowerName[1000];

    XmuCopyISOLatin1Lowered (lowerName, (char*)fromVal->addr);
    q = XrmStringToQuark(lowerName);
    if (q == XtQReliefSimple) {
	relief = XtQReliefSimple;
	done(&relief, XtRelief);
    }
    if (q == XtQReliefRidge) {
	relief = XtQReliefRidge;
	done(&relief, XtRelief);
    }
    if (q == XtQReliefGroove) {
	relief = XtQReliefGroove;
	done(&relief, XtRelief);
    }
    if (q == XtQReliefRaised) {
	relief = XtQReliefRaised;
	done(&relief, XtRelief);
    }
    if (q == XtQReliefFlat) {
	relief = XtQReliefFlat;
	done(&relief, XtRelief);
    }
    if (q == XtQReliefSunken) {
	relief = XtQReliefSunken;
	done(&relief, XtRelief);
    }    
    XtStringConversionWarning(fromVal->addr, "relief");
    toVal->addr = NULL;
    toVal->size = 0;
}

static void _CvtStringToBevel(XrmValuePtr args, Cardinal *num_args,
		XrmValuePtr fromVal, XrmValuePtr toVal)
{
    static XtBevel bevel;
    XrmQuark q;
    char lowerName[1000];

    XmuCopyISOLatin1Lowered (lowerName, (char*)fromVal->addr);
    q = XrmStringToQuark(lowerName);
    if (q == XtQBevelRounded) {
	bevel = XtBevelRounded;
	done(&bevel, XtBevel);
    }
    if (q == XtQBevelSolid) {
	bevel = XtBevelSolid;
	done(&bevel, XtBevel);
    }
    XtStringConversionWarning(fromVal->addr, "bevel");
    toVal->addr = NULL;
    toVal->size = 0;
}

static void ClassInitialize()
{
    XawInitializeWidgetSet();
    /* fprintf(stderr, "ThreeD: ClassInitialize\n"); */
    XtQReliefSimple = XrmPermStringToQuark("simple");
    XtQReliefSunken = XrmPermStringToQuark("sunken");
    XtQReliefFlat   = XrmPermStringToQuark("flat");
    XtQReliefRaised = XrmPermStringToQuark("raised");
    XtQReliefGroove = XrmPermStringToQuark("groove");
    XtQReliefRidge  = XrmPermStringToQuark("ridge");

    XtAddConverter( XtRString, XtRRelief, _CvtStringToRelief, 
		    (XtConvertArgList)NULL, 0 );

    XtQBevelRounded = XrmPermStringToQuark("rounded");
    XtQBevelSolid = XrmPermStringToQuark("solid");

    XtAddConverter(XtRString, XtRBevel, _CvtStringToBevel,
		(XtConvertArgList)NULL, 0);
}


/* ARGSUSED */
static void ClassPartInitialize (wc)
    WidgetClass	wc;

{
    ThreeDClassRec *tdwc = (ThreeDClassRec*) wc;
    ThreeDClassRec *super = (ThreeDClassRec*) tdwc->core_class.superclass;

    if (tdwc->threeD_class.shadowdraw == XtInheritXaw3dShadowDraw)
	tdwc->threeD_class.shadowdraw = super->threeD_class.shadowdraw;
}


/* ARGSUSED */
static void Initialize (request, new, args, num_args)
    Widget request, new;
    ArgList args;
    Cardinal *num_args;
{
    ThreeDWidget 	tdw = (ThreeDWidget) new;
    Screen		*scr = XtScreen (new);

    /* fprintf(stderr, "ThreeD: Initialize (%s)\n", XtClass(new)->core_class.class_name); */
    if (tdw->threeD.be_nice_to_cmap || DefaultDepthOfScreen (scr) == 1) {
	AllocTopShadowPixmap (new);
	AllocBotShadowPixmap (new);
    } else {
	if (tdw->threeD.top_shadow_pixel == tdw->threeD.bot_shadow_pixel) {
	    /* 
		Eeek.  We're probably going to XQueryColor() twice 
		for each widget.  Necessary because you can set the
		top and bottom shadows independent of each other in
		SetValues.  Some cacheing would certainly help...
	    */
	    AllocTopShadowPixel (new);
	    AllocBotShadowPixel (new);
	}
	tdw->threeD.top_shadow_pxmap = tdw->threeD.bot_shadow_pxmap = (Pixmap) 0;
    }
    AllocTopShadowGC (new);
    AllocBotShadowGC (new);
}

static void Realize (gw, valueMask, attrs)
    Widget gw;
    XtValueMask *valueMask;
    XSetWindowAttributes *attrs;
{
 /* 
  * This is necessary because Simple doesn't have a realize method
  * XtInheritRealize in the ThreeD class record doesn't work.  This
  * daisychains through Simple to the Core class realize method
  */
    (*threeDWidgetClass->core_class.superclass->core_class.realize)
	 (gw, valueMask, attrs);
}

static void Destroy (w)
     Widget w;
{
    ThreeDWidget tdw = (ThreeDWidget) w;
    XtReleaseGC (w, tdw->threeD.top_shadow_GC);
    XtReleaseGC (w, tdw->threeD.bot_shadow_GC);
    if (tdw->threeD.top_shadow_pxmap)
	XFreePixmap (XtDisplay (w), tdw->threeD.top_shadow_pxmap);
    if (tdw->threeD.bot_shadow_pxmap)
	XFreePixmap (XtDisplay (w), tdw->threeD.bot_shadow_pxmap);
}

/* ARGSUSED */
static void Redisplay (w, event, region)
    Widget w;
    XEvent *event;		/* unused */
    Region region;		/* unused */
{
    ThreeDWidget tdw = (ThreeDWidget) w;

    switch (tdw->threeD.relief) {
     case XtReliefSunken:
	_Xaw3dDrawShadows (w, event, region, False);
	break;
     case XtReliefRaised:
	_Xaw3dDrawShadows (w, event, region, True);
	break;
     case XtReliefRidge:
	Draw3DFrame(w, event, region, 0);
	break;
     case XtReliefGroove:
	Draw3DFrame(w, event, region, 1);
	break;
     case XtReliefFlat:
	Draw3DFrame(w, event, region, 2);
	break;	
     default:
	;	/* to make ANSI C happy :-) */
    }    
}

/* ARGSUSED */
static Boolean SetValues (gcurrent, grequest, gnew, args, num_args)
    Widget gcurrent, grequest, gnew;
    ArgList args;
    Cardinal *num_args;
{
    ThreeDWidget current = (ThreeDWidget) gcurrent;
    ThreeDWidget new = (ThreeDWidget) gnew;
    Boolean redisplay = FALSE;
    Boolean alloc_top_pixel = FALSE;
    Boolean alloc_bot_pixel = FALSE;
    Boolean alloc_top_pxmap = FALSE;
    Boolean alloc_bot_pxmap = FALSE;

    (*threeDWidgetClass->core_class.superclass->core_class.set_values) 
	(gcurrent, grequest, gnew, NULL, 0);
    if (new->threeD.shadow_width != current->threeD.shadow_width)
	redisplay = TRUE;
    if (new->threeD.be_nice_to_cmap != current->threeD.be_nice_to_cmap) {
	if (new->threeD.be_nice_to_cmap) {
	    alloc_top_pxmap = TRUE;
	    alloc_bot_pxmap = TRUE;
	} else {
	    alloc_top_pixel = TRUE;
	    alloc_bot_pixel = TRUE;
	}
	redisplay = TRUE;
    }
    if (!new->threeD.be_nice_to_cmap &&
	new->threeD.top_shadow_contrast != current->threeD.top_shadow_contrast)
	alloc_top_pixel = TRUE;
    if (!new->threeD.be_nice_to_cmap &&
	new->threeD.bot_shadow_contrast != current->threeD.bot_shadow_contrast)
	alloc_bot_pixel = TRUE;
    if (alloc_top_pixel)
	AllocTopShadowPixel (gnew);
    if (alloc_bot_pixel)
	AllocBotShadowPixel (gnew);
    if (alloc_top_pxmap)
	AllocTopShadowPixmap (gnew);
    if (alloc_bot_pxmap)
	AllocBotShadowPixmap (gnew);
    if (!new->threeD.be_nice_to_cmap &&
	new->threeD.top_shadow_pixel != current->threeD.top_shadow_pixel)
	alloc_top_pixel = TRUE;
    if (!new->threeD.be_nice_to_cmap &&
	new->threeD.bot_shadow_pixel != current->threeD.bot_shadow_pixel)
	alloc_bot_pixel = TRUE;
    if (new->threeD.be_nice_to_cmap) {
	if (alloc_top_pxmap) {
	    XtReleaseGC (gcurrent, current->threeD.top_shadow_GC);
	    XtReleaseGC (gcurrent, current->threeD.top_half_shadow_GC);	    
	    AllocTopShadowGC (gnew);
	    redisplay = True;
	}
	if (alloc_bot_pxmap) {
	    XtReleaseGC (gcurrent, current->threeD.bot_shadow_GC);
	    XtReleaseGC (gcurrent, current->threeD.bot_half_shadow_GC);
	    AllocBotShadowGC (gnew);
	    redisplay = True;
	}
    } else {
	if (alloc_top_pixel) {
	    if (new->threeD.top_shadow_pxmap) {
		XFreePixmap (XtDisplay (gnew), new->threeD.top_shadow_pxmap);
		new->threeD.top_shadow_pxmap = (Pixmap) NULL;
	    }
	    XtReleaseGC (gcurrent, current->threeD.top_shadow_GC);
	    XtReleaseGC (gcurrent, current->threeD.top_half_shadow_GC);
	    AllocTopShadowGC (gnew);
	    redisplay = True;
	}
	if (alloc_bot_pixel) {
	    if (new->threeD.bot_shadow_pxmap) {
		XFreePixmap (XtDisplay (gnew), new->threeD.bot_shadow_pxmap);
		new->threeD.bot_shadow_pxmap = (Pixmap) NULL;
	    }
	    XtReleaseGC (gcurrent, current->threeD.bot_shadow_GC);
	    XtReleaseGC (gcurrent, current->threeD.bot_half_shadow_GC);	    
	    AllocBotShadowGC (gnew);
	    redisplay = True;
	}
    }
    return (redisplay);
}

/* ARGSUSED */
static void
Draw3DFrame (gw, event, region, style)
    Widget gw;
    XEvent *event;
    Region region;
    int style;
{
    XPoint	pt[6];
    ThreeDWidget tdw = (ThreeDWidget) gw;
    Dimension	s = tdw->threeD.shadow_width;
    /* 
     * draw the frame using the core part width and height, 
     * and the threeD part shadow_width.
     *
     *	no point to do anything if the shadow_width is 0 or the
     *	widget has not been realized.
     */ 
    if((s > 0) && XtIsRealized (gw)){

	Dimension	h = tdw->core.height;
	Dimension	w = tdw->core.width;
	Dimension	wms = w - s;
	Dimension	hms = h - s;
	Dimension	wmsm = w - (s>1 ? s/2 : 1);
	Dimension	hmsm = h - (s>1 ? s/2 : 1);
	Dimension	sm = (s>1 ? s/2 : 1);
	Display		*dpy = XtDisplay (gw);
	Window		win = XtWindow (gw);
	GC		top, bot;

	if (style==0) {		/* ridge */
	    top = tdw->threeD.top_shadow_GC;
	    bot = tdw->threeD.bot_half_shadow_GC;
	} else if (style==1) {	/* groove */
	    top = tdw->threeD.bot_half_shadow_GC;
	    bot = tdw->threeD.top_shadow_GC;
	} else {		/* flat */
	    top = bot = tdw->threeD.bot_shadow_GC;
	}

	/* top shadow */
	if ((region == NULL) ||
	    (XRectInRegion (region, 0, 0, w, s) != RectangleOut) ||
	    (XRectInRegion (region, 0, 0, s, h) != RectangleOut)) {
	    
	    pt[0].x = 0;	pt[0].y = h;
	    pt[1].x =		pt[1].y = 0;
	    pt[2].x = w;	pt[2].y = 0;
	    pt[3].x = wmsm;	pt[3].y = sm-1;
	    pt[4].x =		pt[4].y = sm;
	    pt[5].x = sm-1;	pt[5].y = hmsm;
	    XFillPolygon (dpy, win, top, pt, 6,Complex,CoordModeOrigin);
	    if (s > 1) {
		pt[0].x = s-1;	pt[0].y = hms;
	    	pt[1].x =	pt[1].y = s;
	    	pt[2].x = wms;	pt[2].y = s-1;
		XFillPolygon (dpy, win, bot, pt, 6,Complex,CoordModeOrigin);
	    }	    
	}

	/* bottom-right shadow */
	if ((region == NULL) ||
	    (XRectInRegion (region, 0, hms, w, s) != RectangleOut) ||
	    (XRectInRegion (region, wms, 0, s, h) != RectangleOut)) {
	
	    pt[0].x = 0;	pt[0].y = h;
	    pt[1].x = w;	pt[1].y = h;
	    pt[2].x = w;	pt[2].y = 0;
	    pt[3].x = wmsm;	pt[3].y = sm-1;
	    pt[4].x = wmsm;	pt[4].y = hmsm;
	    pt[5].x = sm-1;	pt[5].y = hmsm;
	    XFillPolygon (dpy, win, bot, pt,6, Complex,CoordModeOrigin);
	    if (s > 1) {
		pt[0].x = s-1;	pt[0].y = hms;
	    	pt[1].x = wms;	pt[1].y = hms;
	    	pt[2].x = wms;	pt[2].y = s-1;
		XFillPolygon (dpy, win, top, pt,6, Complex,CoordModeOrigin);
	    }	    
	}
    }
}


/* ARGSUSED */
static void
_Xaw3dDrawShadows (gw, event, region, out)
    Widget gw;
    XEvent *event;
    Region region;
    Boolean out;
{
    XPoint	pt[6];
    ThreeDWidget tdw = (ThreeDWidget) gw;
    Dimension	s = tdw->threeD.shadow_width;
    /* 
     * draw the shadows using the core part width and height, 
     * and the threeD part shadow_width.
     *
     *	no point to do anything if the shadow_width is 0 or the
     *	widget has not been realized.
     */ 

    if((s > 0) && XtIsRealized (gw)){

	Dimension	h = tdw->core.height;
	Dimension	w = tdw->core.width;
	Dimension	wms = w - s;
	Dimension	hms = h - s;
	Dimension	wmsm = w - (s>1 ? s/2 : 1);
	Dimension	hmsm = h - (s>1 ? s/2 : 1);
	Dimension	sm = (s>1 ? s/2 : 1);
	Display		*dpy = XtDisplay (gw);
	Window		win = XtWindow (gw);
	GC		top, bot, toph, both;

	if (out) {
	    top = tdw->threeD.top_shadow_GC;
	    bot = tdw->threeD.bot_shadow_GC;
	    toph = tdw->threeD.top_half_shadow_GC;
	    both = tdw->threeD.bot_half_shadow_GC;
	} else {
	    top = tdw->threeD.bot_shadow_GC;
	    bot = tdw->threeD.top_shadow_GC;
	    toph = tdw->threeD.bot_half_shadow_GC;
	    both = tdw->threeD.top_half_shadow_GC;	    
	}

	if (tdw->threeD.bevel == XtBevelSolid) {
		toph = top;
		both = bot;
	}

	/* top-left shadow */
	if ((region == NULL) ||
	    (XRectInRegion (region, 0, 0, w, s) != RectangleOut) ||
	    (XRectInRegion (region, 0, 0, s, h) != RectangleOut)) {
	    
	    pt[0].x = 0;	pt[0].y = h;
	    pt[1].x =		pt[1].y = 0;
	    pt[2].x = w;	pt[2].y = 0;
	    pt[3].x = wmsm;	pt[3].y = sm-1;
	    pt[4].x =		pt[4].y = sm;
	    pt[5].x = sm-1;	pt[5].y = hmsm;
	    XFillPolygon (dpy, win, toph, pt, 6,Complex,CoordModeOrigin);
	    if (s > 1) {
		pt[0].x = s-1;	pt[0].y = hms;
	    	pt[1].x =	pt[1].y = s;
	    	pt[2].x = wms;	pt[2].y = s-1;
		XFillPolygon (dpy, win, top, pt, 6,Complex,CoordModeOrigin);
	    }	    
	}

	/* bottom-right shadow */
	if ((region == NULL) ||
	    (XRectInRegion (region, 0, hms, w, s) != RectangleOut) ||
	    (XRectInRegion (region, wms, 0, s, h) != RectangleOut)) {
	
	    pt[0].x = 0;	pt[0].y = h;
	    pt[1].x = w;	pt[1].y = h;
	    pt[2].x = w;	pt[2].y = 0;
	    pt[3].x = wmsm;	pt[3].y = sm-1;
	    pt[4].x = wmsm;	pt[4].y = hmsm;
	    pt[5].x = sm-1;	pt[5].y = hmsm;
	    XFillPolygon (dpy, win, both, pt,6, Complex,CoordModeOrigin);
	    if (s > 1) {
		pt[0].x = s-1;	pt[0].y = hms;
	    	pt[1].x = wms;	pt[1].y = hms;
	    	pt[2].x = wms;	pt[2].y = s-1; 
		XFillPolygon (dpy, win, bot, pt,6, Complex,CoordModeOrigin);
	    }	    
	}
    }
}
