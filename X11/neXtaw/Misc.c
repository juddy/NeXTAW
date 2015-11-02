/*
 * Misc. functions for neXtaw 
 * 
 * Copyright (c) 1996 Alfedo K. Kojima
 */

#include "Misc.h"

#ifdef XPM_TILE
#include <X11/xpm.h>
#endif

void
neXtawDrawShadowBox (gw, tdw, x0, y0, x1, y1, out) 
    Widget gw;
    ThreeDWidget tdw;
    Position x0, y0, x1, y1;
    Boolean out;
{
    XPoint	pt[6];
    Dimension	s = tdw->threeD.shadow_width;
    
    /* 
     * draw the shadows using the core part width and height, 
     * and the threeD part shadow_width.
     *
     *	no point to do anything if the shadow_width is 0 or the
     *	widget has not been realized.
     */ 
    if((s > 0) && XtIsRealized (gw)){

	Dimension	h = y1 - y0;
	Dimension	w = x1 - x0;
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
	pt[0].x = x0;		pt[0].y = y0+h;
	pt[1].x = x0;		pt[1].y = y0;
	pt[2].x = x0+w;		pt[2].y = y0;
	pt[3].x = x0+wmsm;	pt[3].y = y0+sm-1;
	pt[4].x = x0+sm;	pt[4].y = y0+sm;
	pt[5].x = x0+sm-1;	pt[5].y = y0+hmsm;
	XFillPolygon (dpy, win, toph, pt, 6,Complex,CoordModeOrigin);
	if (s > 1) {
	    pt[0].x = x0+s-1;	pt[0].y = y0+hms;
	    pt[1].x = x0+s;	pt[1].y = y0+s;
	    pt[2].x = x0+wms;	pt[2].y = y0+s-1;
	    XFillPolygon (dpy, win, top, pt, 6,Complex,CoordModeOrigin);
	}	    

	/* bottom-right shadow */	
	pt[0].x = x0;		pt[0].y = y0+h;
	pt[1].x = x0+w;		pt[1].y = y0+h;
	pt[2].x = x0+w;		pt[2].y = y0;
	pt[3].x = x0+wmsm;	pt[3].y = y0+sm-1;
	pt[4].x = x0+wmsm;	pt[4].y = y0+hmsm;
	pt[5].x = x0+sm-1;	pt[5].y = y0+hmsm;
	XFillPolygon (dpy, win, both, pt,6, Complex,CoordModeOrigin);
	if (s > 1) {
	    pt[0].x = x0+s-1;	pt[0].y = y0+hms;
	    pt[1].x = x0+wms;	pt[1].y = y0+hms;
	    pt[2].x = x0+wms;	pt[2].y = y0+s-1;
	    XFillPolygon (dpy, win, bot, pt,6, Complex,CoordModeOrigin);
	}	    
    }
}



#ifdef XPM_TILE
Boolean
neXtawcvtStringToTilePixmap ( display, args, num_args,  from, to, converter_data)
     Display *display;
     XrmValue *args;
     Cardinal *num_args;
     XrmValuePtr from;
     XrmValuePtr to;
     XtPointer *converter_data;
{
    String file = (String) from->addr;
    XpmAttributes attr;
    Pixmap pixmap, mask;
    Window win;

    if (*num_args != 2)
          XtAppErrorMsg(XtDisplayToApplicationContext(display),
		  "cvtStringToTilePixmap", "wrongParameters",
		  "XtToolkitError",
		  "String to TilePixmap conversion needs screen and colormap arguments",
		  (String*) NULL, (Cardinal*) NULL);
    win = RootWindow(display, 
		     XScreenNumberOfScreen(*((Screen **)args[0].addr)));
    attr.colormap = *((Colormap *)args[1].addr);
    attr.valuemask = XpmSize | XpmReturnPixels|XpmColormap;
    if(XpmReadFileToPixmap(display, win, file, &pixmap, &mask,
			   &attr) != XpmSuccess) {
	XtDisplayStringConversionWarning(display, file, XtRTilePixmap);
	return False;
    } 
    if (mask!=None)
      XFreePixmap(display, mask);
    if (to->addr!=NULL) {
	if (to->size < sizeof(Pixmap)) {
	    to->size = sizeof(Pixmap);
	    XtDisplayStringConversionWarning(display, file, XtRTilePixmap);
	    return False;
	}
	*(Pixmap*)(to->addr) = pixmap;
    } else {
	static Pixmap s_pixmap;

	s_pixmap = pixmap;
	to->addr = (XtPointer)&s_pixmap;
    }
    to->size = sizeof(Pixmap);
    return True;
}
#endif /* XPM_TILE */
