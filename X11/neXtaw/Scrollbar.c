/* MODIFIED ATHENA SCROLLBAR (USING ARROWHEADS AT ENDS OF TRAVEL) */
/* Modifications Copyright 1992 by Mitch Trachtenberg             */
/* Rights, permissions, and disclaimer of warranty are as in the  */
/* DEC and MIT notice below.                                      */
/* $XConsortium: Scrollbar.c,v 1.70 91/10/16 21:39:40 eswu Exp $ */

/* MODIFIED FOR N*XTSTEP LOOK	 				*/
/* Modifications Copyright (c) 1996, 1997 by Alfredo Kojima	*/
/***********************************************************

Copyright (c) 1987, 1988, 1994  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/* ScrollBar.c */
/* created by weissman, Mon Jul  7 13:20:03 1986 */
/* converted by swick, Thu Aug 27 1987 */

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include "XawInit.h"
#include "ScrollbarP.h"
#include "TraversalP.h"
#include "Misc.h"
#include <X11/Xmu/Drawing.h>

/* Private definitions. */

static char defaultTranslations[] =
    "<Btn1Down>:   NotifyScroll()\n\
     <Btn2Down>:   MoveThumb() NotifyThumb() \n\
     <Btn3Down>:   NotifyScroll()\n\
     <Btn1Motion>: HandleThumb() \n\
     <Btn3Motion>: HandleThumb() \n\
     <Btn2Motion>: MoveThumb() NotifyThumb() \n\
     <Btn4Down>:   ScrollOneLineUp()\n\
     <Btn5Down>:   ScrollOneLineDown()\n\
     Shift<Btn4Down>: ScrollPageUp()\n\
     Shift<Btn5Down>: ScrollPageDown()\n\
     <BtnUp>:      EndScroll()			\n\
     <EnterWindow>:	FocusEnterWindow()	\n\
     <LeaveWindow>:	FocusLeaveWindow()	\n\
     Shift<Key>Tab:	FocusPrevious()		\n\
     <Key>Tab:		FocusNext()		\n\
     <KeyDown>Left:	NotifyScroll(BackwardArrow)	\n\
     <KeyDown>Up:	NotifyScroll(BackwardArrow)	\n\
     <KeyDown>Right:	NotifyScroll(ForwardArrow)	\n\
     <KeyDown>Down:	NotifyScroll(ForwardArrow)	\n\
     <KeyDown>Page_Up:	NotifyScroll(BackwardPage)	\n\
     <KeyDown>Page_Down:	NotifyScroll(ForwardPage)	\n\
     <KeyDown>Home:	NotifyScroll(Home)		\n\
     <KeyDown>End:	NotifyScroll(End)		\n\
     <KeyDown>KP_Left:	NotifyScroll(BackwardArrow)	\n\
     <KeyDown>KP_Up:	NotifyScroll(BackwardArrow)	\n\
     <KeyDown>KP_Right:	NotifyScroll(ForwardArrow)	\n\
     <KeyDown>KP_Down:	NotifyScroll(ForwardArrow)	\n\
     <KeyDown>KP_Page_Up:	NotifyScroll(BackwardPage)	\n\
     <KeyDown>KP_Page_Down:	NotifyScroll(ForwardPage)	\n\
     <KeyDown>KP_Home:		NotifyScroll(Home)		\n\
     <KeyDown>KP_End:		NotifyScroll(End)		";

static float floatZero = 0.0;

/* minimum space inside of scrollbar to draw pixmaps in it*/
#define MIN_WIDTH_TO_DRAW	6

#define Offset(field) XtOffsetOf(ScrollbarRec, scrollbar.field)

static XtResource resources[] = {
  {XtNlength, XtCLength, XtRDimension, sizeof(Dimension),
       Offset(length), XtRImmediate, (XtPointer) 1},
  {XtNthickness, XtCThickness, XtRDimension, sizeof(Dimension),
       Offset(thickness), XtRImmediate, (XtPointer) 20},
  {XtNorientation, XtCOrientation, XtROrientation, sizeof(XtOrientation),
      Offset(orientation), XtRImmediate, (XtPointer) XtorientVertical},
  {XtNscrollProc, XtCCallback, XtRCallback, sizeof(XtPointer),
       Offset(scrollProc), XtRCallback, NULL},
  {XtNthumbProc, XtCCallback, XtRCallback, sizeof(XtPointer),
       Offset(thumbProc), XtRCallback, NULL},
  {XtNjumpProc, XtCCallback, XtRCallback, sizeof(XtPointer),
       Offset(jumpProc), XtRCallback, NULL},
  {XtNthumb, XtCThumb, XtRBitmap, sizeof(Pixmap),
       Offset(thumb), XtRImmediate, (XtPointer) XtUnspecifiedPixmap},
  {XtNforeground, XtCForeground, XtRPixel, sizeof(Pixel),
       Offset(foreground), XtRString, XtDefaultForeground},
  {XtNshown, XtCShown, XtRFloat, sizeof(float),
       Offset(shown), XtRFloat, (XtPointer)&floatZero},
  {XtNtopOfThumb, XtCTopOfThumb, XtRFloat, sizeof(float),
       Offset(top), XtRFloat, (XtPointer)&floatZero},
  {XtNpickTop, XtCPickTop, XtRBoolean, sizeof(Boolean),
       Offset(pick_top), XtRBoolean, (XtPointer) False},
  {XtNminimumThumb, XtCMinimumThumb, XtRDimension, sizeof(Dimension),
       Offset(min_thumb), XtRImmediate, (XtPointer) 6},
  /* AKK, 1996 */
  {XtNdrawArrows, XtCDrawArrows, XtRBoolean, sizeof(Boolean),
       Offset(draw_arrows), XtRImmediate, (XtPointer) TRUE},
  {XtNdrawBump, XtCDrawBump, XtRBoolean, sizeof(Boolean),
       Offset(draw_bump), XtRImmediate, (XtPointer) TRUE},
  {XtNalwaysVisible, XtCAlwaysVisible, XtRBoolean, sizeof(Boolean),
       Offset(always_visible), XtRImmediate, (XtPointer) False},
  /* Casantos, feb/2000 */
  { XtNinitialDelay, XtCDelay, XtRInt, sizeof (int),
       Offset(initial_delay), XtRImmediate, (XtPointer) SB_DEF_INITIAL_DELAY },
  { XtNrepeatDelay, XtCDelay, XtRInt, sizeof (int),
       Offset(repeat_delay), XtRImmediate, (XtPointer) SB_DEF_REPEAT_DELAY },
};
#undef Offset

static void ClassInitialize();
static void Initialize();
static void Destroy();
static void Realize();
static void Resize();
static void Redisplay();
static Boolean SetValues();

static void HandleThumb();
static void MoveThumb();
static void NotifyThumb();
static void NotifyScroll();
static void ScrollOneLineUp();
static void ScrollPageUp();
static void ScrollOneLineDown();
static void ScrollPageDown();
static void EndScroll();

static void PaintArrowButtons();
static void DrawArrow();

static XtActionsRec actions[] = {
    {"HandleThumb",	HandleThumb},
    {"MoveThumb",	MoveThumb},
    {"NotifyThumb",	NotifyThumb},
    {"NotifyScroll",	NotifyScroll},
    {"ScrollOneLineUp",	ScrollOneLineUp},
    {"ScrollPageUp",	ScrollPageUp},
    {"ScrollOneLineDown",	ScrollOneLineDown},
    {"ScrollPageDown",	ScrollPageDown},
    {"EndScroll",	EndScroll}
};


ScrollbarClassRec scrollbarClassRec = {
  { /* core fields */
    /* superclass       */	(WidgetClass) &threeDClassRec,
    /* class_name       */	"Scrollbar",
    /* size             */	sizeof(ScrollbarRec),
    /* class_initialize	*/	ClassInitialize,
    /* class_part_init  */	NULL,
    /* class_inited	*/	FALSE,
    /* initialize       */	Initialize,
    /* initialize_hook  */	NULL,
    /* realize          */	Realize,
    /* actions          */	actions,
    /* num_actions	*/	XtNumber(actions),
    /* resources        */	resources,
    /* num_resources    */	XtNumber(resources),
    /* xrm_class        */	NULLQUARK,
    /* compress_motion	*/	TRUE,
    /* compress_exposure*/	TRUE,
    /* compress_enterleave*/	TRUE,
    /* visible_interest */	FALSE,
    /* destroy          */	Destroy,
    /* resize           */	Resize,
    /* expose           */	Redisplay,
    /* set_values       */	SetValues,
    /* set_values_hook  */	NULL,
    /* set_values_almost */	XtInheritSetValuesAlmost,
    /* get_values_hook  */	NULL,
    /* accept_focus     */	XawAcceptFocus,
    /* version          */	XtVersion,
    /* callback_private */	NULL,
    /* tm_table         */	defaultTranslations,
    /* query_geometry	*/	XtInheritQueryGeometry,
    /* display_accelerator*/	XtInheritDisplayAccelerator,
    /* extension        */	NULL
  },
  { /* simple fields */
    /* change_sensitive	*/	XtInheritChangeSensitive
  },
  { /* threeD fields */
    /* shadowdraw	*/	XtInheritXaw3dShadowDraw
  },
  { /* scrollbar fields */
    /* ignore		*/	0
  }

};

WidgetClass scrollbarWidgetClass = (WidgetClass)&scrollbarClassRec;


#define SHADOWPM_SIZE 2
static char shadowpm_bits[] = {
   0x02, 0x01};

 
#define SB_BUMP_SIZE  6
static char scrollbar_bump[] = {
" dbbb "\
"dbdddd"\
"bdd   "\
"bd  ww"\
"bd www"\
" d ww "
};


#define NoButton -1
#define PICKLENGTH(widget, x, y) \
    ((widget->scrollbar.orientation == XtorientHorizontal) ? (x) : (y))
#define MIN(x,y)	((x) < (y) ? (x) : (y))
#define MAX(x,y)	((x) > (y) ? (x) : (y))

static void ClassInitialize()
{
    XawInitializeWidgetSet();
    XtAddConverter( XtRString, XtROrientation, XmuCvtStringToOrientation,
		    (XtConvertArgList)NULL, (Cardinal)0 );
}

/* CHECKIT #define MARGIN(sbw) (sbw)->scrollbar.thickness + (sbw)->threeD.shadow_width */
/* CHECKIT #define MARGIN(sbw) ((sbw)->scrollbar.draw_arrows ? (sbw)->scrollbar.thickness : (sbw)->threeD.shadow_width) */
#define MARGIN(sbw) ((sbw)->scrollbar.draw_arrows ? (sbw)->scrollbar.thickness\
			: 0)

/* 
 The original Xaw Scrollbar's FillArea *really* relied on the fact that the 
 server was going to clip at the window boundaries; so the logic was really
 rather sloppy.  To avoid drawing over the shadows and the arrows requires 
 some extra care...  Hope I didn't make any mistakes.
*/
static void FillArea (sbw, top, bottom, fill)
    ScrollbarWidget sbw;
    Position top, bottom;
    int fill;
{
    int tlen = bottom - top;	/* length of thumb in pixels */
    int sw, margin, floor;
    int lx, ly, lw, lh;
    
    if (fill == 4) {
	XFillRectangle(XtDisplay((Widget) sbw), XtWindow((Widget) sbw), 
			sbw->scrollbar.bgc,
			1, 1, (unsigned int) sbw->core.width - 1,
		       (unsigned int) sbw->core.height - 1);
	return;
    }
    if (bottom <= 0 || bottom <= top) 
	return;
    if ((sw = sbw->threeD.shadow_width) < 0) 
	sw = 0;

    if (sbw->scrollbar.orientation == XtorientHorizontal) {
	margin = MARGIN (sbw) * 2 - 1;
	floor = sbw->scrollbar.length - 1;
	
	lx = ((top < margin) ? margin : top);
	ly = 1;
	lw = ((bottom > floor) ? floor - top : tlen);
/* CHECKIT	lw = (((top + tlen) > floor) ? floor - top : tlen); */
	lh = sbw->core.height - 1;
    } else {
	margin = 1;
	floor = sbw->scrollbar.length - ((MARGIN (sbw) - 2)*2);

	lx = 1;
	ly = ((top < margin) ? margin : top);
	lw = sbw->core.width - 1;
/* CHECKIT	lh = (((top + tlen) > floor) ? floor - top : tlen); */
	lh = ((bottom > floor) ? floor - top : tlen);
    }
    if (lh <= 0 || lw <= 0) return;
    if (fill==1) {
	XFillRectangle(XtDisplay((Widget) sbw), XtWindow((Widget) sbw), 
			sbw->scrollbar.gc,
			lx, ly, (unsigned int) lw, (unsigned int) lh);
    } else if (fill==2) {
       	XFillRectangle(XtDisplay((Widget) sbw), XtWindow((Widget) sbw), 
			sbw->scrollbar.bgc,
			lx, ly, (unsigned int) lw, (unsigned int) lh);
    } else if (2*sw<lw && 2*sw<lh) {
	XClearArea (XtDisplay((Widget) sbw), XtWindow((Widget) sbw), 
		    lx+sw, ly+sw, (unsigned int) lw-2*sw, (unsigned int) lh-2*sw,
		    FALSE);
    }
}
#if 0
    if ((sw = sbw->threeD.shadow_width) < 0) 
	sw = 0;
    margin = MARGIN (sbw);
    floor = sbw->scrollbar.length - margin;

    if (sbw->scrollbar.orientation == XtorientHorizontal) {
	lx = ((top < margin) ? margin : top);
	ly = sw;
	lw = ((bottom > floor) ? floor - top : tlen);
/* CHECKIT	lw = (((top + tlen) > floor) ? floor - top : tlen); */
	lh = sbw->core.height - 2 * sw;
    } else {
	lx = sw;
	ly = ((top < margin) ? margin : top);
	lw = sbw->core.width - 2 * sw;
/* CHECKIT	lh = (((top + tlen) > floor) ? floor - top : tlen); */
	lh = ((bottom > floor) ? floor - top : tlen);
    }
    if (lh <= 0 || lw <= 0) return;
    if (fill==1) {
	XFillRectangle(XtDisplay((Widget) sbw), XtWindow((Widget) sbw), 
			sbw->scrollbar.gc,
			lx, ly, (unsigned int) lw, (unsigned int) lh);
    } else if (fill==2) {
       	XFillRectangle(XtDisplay((Widget) sbw), XtWindow((Widget) sbw), 
			sbw->scrollbar.bgc,
			lx, ly, (unsigned int) lw, (unsigned int) lh);
    } else if (2*sw<lw && 2*sw<lh) {
	XClearArea (XtDisplay((Widget) sbw), XtWindow((Widget) sbw), 
			lx, ly, (unsigned int) lw, (unsigned int) lh,
			FALSE);
    }
}
#endif

/*
 * Draws an arrow with direction dir and size w x h. It's coordinates
 * are relative to the top-left corner of the arrow's envelope
 */
static void DrawArrow(sbw, x, y, w, h, vert, up)
    ScrollbarWidget sbw;
    Position 	x, y;	/* position relative to middle of arrow */
    Dimension 	w, h;
    char	vert, up;
{
    int i, hw;
    float d, s;
    GC 	core, border;

    core = sbw->threeD.bot_half_shadow_GC;
    border = sbw->threeD.bot_shadow_GC;
    x += w/2;
    y += h/2;    
    if (h<3) h=3;
    if (w<3) w=3;
    if (vert) { /* vertical */
	hw = w/2;
	d = ((float)w/2)/(float)h;
	y -= h/2;	
    } else {
	hw = h/2;
	d = ((float)h/2)/(float)w;
	x -= w/2;
    }
    
    if (up) { /* up/left */
	s = 0;
    } else {
	s=h*d+0.5;
	d=-d;
    }
    
    if (vert) {
	for(i = 0; i < h; i++) {
	    s += d;	
	    XDrawLine(XtDisplay(sbw), XtWindow(sbw), core,
		      (unsigned)(x-(int)(s-0.5)), y+i,
		      (unsigned)(x+(int)(s-0.5)), y+i);
	    /* anti-aliasing */	
	    if ((int)(s+0.5)!=(int)s) {
		XDrawPoint(XtDisplay(sbw), XtWindow(sbw), border,
			   (unsigned)(x+(int)s), y+i);
		XDrawPoint(XtDisplay(sbw), XtWindow(sbw), border,
			   (unsigned)(x-(int)s), y+i);
	    }
	}
    } else {
	for(i = 0; i < h; i++) {
	    s += d;	
	    XDrawLine(XtDisplay(sbw), XtWindow(sbw), core,
		      x+i,(unsigned)(y-(int)(s-0.5)),
		      x+i,(unsigned)(y+(int)(s-0.5)));
	    /* anti-aliasing */	
	    if ((int)(s+0.5)!=(int)s) {
		XDrawPoint(XtDisplay(sbw), XtWindow(sbw), border,
			   x+i,(unsigned)(y+(int)s));
		XDrawPoint(XtDisplay(sbw), XtWindow(sbw), border,
			   x+i,(unsigned)(y-(int)s));
	    }
	}
    }
}

static void PaintArrowButtons(sbw, event, tpush, bpush)
    ScrollbarWidget sbw;
    XEvent *event;
    Boolean tpush, bpush;
{
    Dimension s                   = sbw->threeD.shadow_width;
    Dimension bsize		  = MARGIN (sbw) - 2;
    Position  floor               = sbw->scrollbar.length - 2*bsize - 2;
    Display   *dpy		  = XtDisplay((Widget)sbw);
    Window    w			  = XtWindow((Widget)sbw);
    Dimension tpd, bpd;   /* "depth" of the push */
    Dimension arrsize 		  = bsize - 2*s - 2;

    if ((sbw->scrollbar.shown >= 1.0) && (!sbw->scrollbar.always_visible))
      return;
    if (!XtIsRealized((Widget)sbw))
      return;
    tpd = (tpush ? s/2 : 0);
    bpd = (bpush ? s/2 : 0);
    if (sbw->scrollbar.orientation == XtorientHorizontal) {
	if (tpush>=0) {
	    XClearArea(dpy, w, s + 1, s + 1, bsize + 1 - 2*s, 
		       sbw->core.height - 2*s, False);
	    neXtawDrawShadowBox(
				(Widget)sbw, (ThreeDWidget)sbw, 1, 1,
				2 + bsize, sbw->core.height, !tpush);
	    if ((bsize - 2 * s) >= MIN_WIDTH_TO_DRAW) {
		DrawArrow(sbw, 2 + s + tpd, 2 + s + tpd, arrsize, arrsize,
			  0, 1);
	    }	    
	}
	if (bpush>=0) {
	    XClearArea(dpy, w, bsize + 2 + s, 
		       1 + s, 2 + bsize - 2*s, 
		       sbw->core.height - 2*s, False);	
	    neXtawDrawShadowBox(
				(Widget)sbw, (ThreeDWidget)sbw, bsize + 2, 1,
				2*bsize + 3, sbw->core.height,!bpush);
	    if ((bsize - 2 * s) >= MIN_WIDTH_TO_DRAW) {	    
		DrawArrow(sbw, 2 + bsize + s + 1 + bpd, 2 + s + bpd,
			  arrsize, arrsize, 0, 0);
	    }
	}	    
    } else {
	if (tpush>=0) {
	    XClearArea(dpy, w, 1+s, floor + s,
		       sbw->core.width - 2*s,
		       sbw->core.width - 2*s, False);
	    neXtawDrawShadowBox(
				(Widget)sbw, (ThreeDWidget)sbw, 1, floor,
				sbw->core.width, floor + bsize + 1,!tpush);
	    if ((bsize - 2 * s) >= MIN_WIDTH_TO_DRAW) {
		DrawArrow(sbw, 2 + s + tpd, floor + s + tpd, arrsize,
			  arrsize, 1, 1);
	    }
	}
	if (bpush>=0) {
	    XClearArea(dpy, w, 1+s, floor + bsize + 1+s,
		       sbw->core.width - 2*s,
		       sbw->core.width - 2*s, False);	
	    neXtawDrawShadowBox(
				(Widget)sbw, (ThreeDWidget)sbw, 1, floor + bsize + 1,
				sbw->core.width,floor + 2*(bsize+1),!bpush);
	    if ((bsize - 2 * s) >= MIN_WIDTH_TO_DRAW) {	
		DrawArrow(sbw, 2 + s + bpd, floor + 2 + bsize + s + bpd,
			  arrsize, arrsize, 1, 0);
	    }	    
	}	
    }
}


/* Paint the thumb in the area specified by sbw->top and
   sbw->shown.  The old area is erased.  */

static void PaintThumb (sbw, event)
    ScrollbarWidget sbw;
    XEvent *event;
{
    Dimension s                   = sbw->threeD.shadow_width;
    Position  oldtop              = sbw->scrollbar.topLoc;
    Position  oldbot              = oldtop + sbw->scrollbar.shownLength;
    Dimension bsize		  = (sbw->scrollbar.draw_arrows ? 
				     	MARGIN (sbw) - 1
				        : 0);
    Dimension start;
    Dimension tzl                 = sbw->scrollbar.length - 2*bsize;
    Position newtop, newbot;
    Position  floor               = sbw->scrollbar.length;

    if (sbw->scrollbar.orientation == XtorientHorizontal) {
	start = bsize * 2 + 1;
	floor -= 1;
    } else {
	start = 1;
	floor -= (bsize * 2);
    }    

    newtop = start + (int)(tzl * sbw->scrollbar.top);
    newbot = newtop + (int)(tzl * sbw->scrollbar.shown);
    if (sbw->scrollbar.shown < 1.) newbot++;
    if (newbot < newtop + (int)sbw->scrollbar.min_thumb +
                        2 * (int)sbw->threeD.shadow_width) 
      newbot = newtop + sbw->scrollbar.min_thumb +
                        2 * sbw->threeD.shadow_width;

    if ( newbot >= floor ) {
	newtop = floor-(newbot-newtop)+1;
	newbot = floor;
    }
    sbw->scrollbar.topLoc = newtop;

    sbw->scrollbar.shownLength = newbot - newtop;
    if (XtIsRealized ((Widget) sbw)) {
	XDrawRectangle(XtDisplay((Widget) sbw), XtWindow((Widget) sbw),
		       sbw->threeD.bot_half_shadow_GC,
		       0, 0, sbw->core.width, sbw->core.height);
	if ((sbw->scrollbar.shown >= 1.0) && (!sbw->scrollbar.always_visible)) {
	    FillArea(sbw, 0, 0, 4);
	    return;
	}
	if ((sbw->scrollbar.scroll_mode==0) && (sbw->scrollbar.draw_arrows))
		  PaintArrowButtons(sbw, event, FALSE, FALSE);	
      /*  3D thumb wanted ?
       */
      if (s)
	  {
	  if (oldtop < 0) {
	      FillArea(sbw, start, newtop, 2);
	      FillArea(sbw, newbot, floor, 2);
	  } else {
	      FillArea(sbw, start, MIN(newtop, oldbot), 2);
	      FillArea(sbw, MAX(newbot, oldtop-s), floor, 2);
	  }
	  FillArea(sbw, newtop, newbot, 0);
          if (sbw->scrollbar.orientation == XtorientHorizontal)
	      {
		if ((bsize - 2*s) >= SB_BUMP_SIZE) {
		   int newb=newbot-newtop; 

		    if (sbw->scrollbar.draw_bump) {
		      XCopyArea(XtDisplay((Widget)sbw), sbw->scrollbar.bump, 
			XtWindow((Widget)sbw),
                     	sbw->scrollbar.copygc, 0, 0, SB_BUMP_SIZE, SB_BUMP_SIZE,
		     	newtop+(newb-SB_BUMP_SIZE)/2,
		     	(sbw->core.height-SB_BUMP_SIZE)/2);
		    }
		}
		neXtawDrawShadowBox(
		  	(Widget)sbw, (ThreeDWidget)sbw, newtop, 1,
		  	newbot, sbw->core.height, TRUE);
	      }
	  else 
	      {
		if ((bsize - 2 * s)>= SB_BUMP_SIZE) {
		   int newb = newbot-newtop;

		    if (sbw->scrollbar.draw_bump) {
		      XCopyArea(XtDisplay((Widget)sbw), sbw->scrollbar.bump,
                     	XtWindow((Widget)sbw),
                     	sbw->scrollbar.copygc, 0, 0, SB_BUMP_SIZE, 
			SB_BUMP_SIZE, (sbw->core.width-SB_BUMP_SIZE)/2,
		     	newtop+(newb-SB_BUMP_SIZE)/2);
		    }
		}
		neXtawDrawShadowBox(
		  (Widget)sbw, (ThreeDWidget)sbw, 1, newtop,
		  sbw->core.width, newbot,
		  TRUE);		  
	      }
	  }
      else 
	  {
	  /* 
	    Note to Mitch: FillArea is (now) correctly implemented to 
	    not draw over shadows or the arrows. Therefore setting clipmasks 
	    doesn't seem to be necessary.  Correct me if I'm wrong!
	  */
          if (newtop < oldtop) FillArea(sbw, newtop, MIN(newbot, oldtop), 1);
          if (newtop > oldtop) FillArea(sbw, oldtop, MIN(newtop, oldbot), 0);
          if (newbot < oldbot) FillArea(sbw, MAX(newbot, oldtop), oldbot, 0);
          if (newbot > oldbot) FillArea(sbw, MAX(newtop, oldbot), newbot, 1);
	  }
    }
}

/*	Function Name: Destroy
 *	Description: Called as the scrollbar is going away...
 *	Arguments: w - the scrollbar.
 *	Returns: nonw
 */
static void Destroy (w)
    Widget w;
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    if(sbw->scrollbar.timer_id != (XtIntervalId) 0)
	XtRemoveTimeOut (sbw->scrollbar.timer_id);
    XtReleaseGC (w, sbw->scrollbar.gc);
    XtReleaseGC (w, sbw->scrollbar.bgc);
    XtReleaseGC (w, sbw->scrollbar.copygc);
    if(sbw->scrollbar.stipple)
	XFreePixmap(XtDisplay(w), sbw->scrollbar.stipple);
    XFreePixmap(XtDisplay(w), sbw->scrollbar.bump);
}


/*
 * Very ugly pixmap maker.
 */
static void PaintPixmap(sbw, d, data, width, height)
    ScrollbarWidget sbw;
    Drawable d;
    char *data;
    int width, height;
{
    int x, y, ofs=0;
    Display *display = XtDisplay((Widget)sbw);
    GC lightGC, backGC, darkGC, dark2GC;

    backGC = sbw->threeD.top_shadow_GC;
    lightGC = sbw->threeD.top_half_shadow_GC;
    darkGC = sbw->threeD.bot_shadow_GC;
    dark2GC = sbw->threeD.bot_half_shadow_GC;

    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            switch (data[ofs++]) {
             case 'b': /* black */
                XDrawPoint( display, d, dark2GC, x, y);
                break;
             case 'd': /* dark */
                XDrawPoint( display, d, darkGC, x, y);
                break;
             case 'w': /* white */
                XDrawPoint( display, d, lightGC, x, y);
                break;
             default:
                XDrawPoint( display, d, backGC, x, y);
            }
        }
    }
}


/*	Function Name: CreateGC
 *	Description: Creates the GC.
 *	Arguments: w - the scrollbar widget.
 *	Returns: none. 
 */

static void CreateGC (w)
    Widget w;
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    XGCValues gcValues;
    XtGCMask mask;
    unsigned int depth = 1;

    if (sbw->scrollbar.thumb == XtUnspecifiedPixmap) {
        sbw->scrollbar.thumb = XmuCreateStippledPixmap (XtScreen(w), 
					(Pixel) 1, (Pixel) 0, depth);
    } else if (sbw->scrollbar.thumb != None) {
	Window root;
	int x, y;
	unsigned int width, height, bw;
	if (XGetGeometry (XtDisplay(w), sbw->scrollbar.thumb, &root, &x, &y,
			 &width, &height, &bw, &depth) == 0) {
	    XtAppError (XtWidgetToApplicationContext (w),
	       "Scrollbar Widget: Could not get geometry of thumb pixmap.");
	}
    }

    gcValues.foreground = /*sbw->scrollbar.foreground;*/
      WhitePixelOfScreen(XtScreen(sbw));
    gcValues.background = sbw->core.background_pixel;
    mask = GCForeground | GCBackground;

    if (sbw->scrollbar.thumb != None) {
	if (depth == 1) {
	    gcValues.fill_style = FillOpaqueStippled;
	    gcValues.stipple = sbw->scrollbar.thumb;
	    mask |= GCFillStyle | GCStipple;
	}
	else {
	    gcValues.fill_style = FillTiled;
	    gcValues.tile = sbw->scrollbar.thumb;
	    mask |= GCFillStyle | GCTile;
	}
    }
    /* the creation should be non-caching, because */
    /* we now set and clear clip masks on the gc returned */
    sbw->scrollbar.gc = XtGetGC (w, mask, &gcValues);

    /* GC for XCopyArea */
    gcValues.graphics_exposures = False;
    sbw->scrollbar.copygc = XtGetGC(w, GCGraphicsExposures, &gcValues);

    /* make GC for scrollbar background */
    if (sbw->threeD.be_nice_to_cmap ||
        DefaultDepthOfScreen (XtScreen(w)) == 1) {
        mask = GCTile | GCFillStyle;
        gcValues.tile = sbw->threeD.bot_shadow_pxmap;
        gcValues.fill_style = FillTiled;
	sbw->scrollbar.stipple = 0;
    } else {
        sbw->scrollbar.stipple = XCreateBitmapFromData (XtDisplay(w),
                        RootWindowOfScreen (XtScreen(w)),shadowpm_bits,
                        SHADOWPM_SIZE, SHADOWPM_SIZE);
        gcValues.fill_style = FillOpaqueStippled;
        gcValues.stipple = sbw->scrollbar.stipple;
        gcValues.background = sbw->threeD.bot_shadow_pixel;
        gcValues.foreground = sbw->threeD.top_shadow_pixel;         
        mask = GCFillStyle | GCStipple |GCForeground|GCBackground;
    }
    sbw->scrollbar.bgc = XtGetGC(w, mask, &gcValues);
    
    /* create bump for the thumb */
    sbw->scrollbar.bump=XCreatePixmap( XtDisplay(w), 
                                      RootWindowOfScreen (XtScreen(w)),
                                      SB_BUMP_SIZE, SB_BUMP_SIZE,
                                      w->core.depth );
    PaintPixmap(sbw, sbw->scrollbar.bump, scrollbar_bump,
                SB_BUMP_SIZE, SB_BUMP_SIZE);
}

static void SetDimensions (sbw)
    ScrollbarWidget sbw;
{
    if (sbw->scrollbar.orientation == XtorientVertical) {
	sbw->scrollbar.length = sbw->core.height;
	sbw->scrollbar.thickness = sbw->core.width;
    } else {
	sbw->scrollbar.length = sbw->core.width;
	sbw->scrollbar.thickness = sbw->core.height;
    }
}

/* ARGSUSED */
static void Initialize( request, new, args, num_args )
    Widget request;		/* what the client asked for */
    Widget new;			/* what we're going to give him */
    ArgList args;
    Cardinal *num_args;
{
    ScrollbarWidget sbw = (ScrollbarWidget) new;

    CreateGC (new);

    if (sbw->core.width == 0)
	sbw->core.width = (sbw->scrollbar.orientation == XtorientVertical)
	    ? sbw->scrollbar.thickness : sbw->scrollbar.length;

    if (sbw->core.height == 0)
	sbw->core.height = (sbw->scrollbar.orientation == XtorientHorizontal)
	    ? sbw->scrollbar.thickness : sbw->scrollbar.length;

    SetDimensions (sbw);
    sbw->scrollbar.scroll_mode = 0;
    sbw->scrollbar.timer_id = (XtIntervalId)0;
    sbw->scrollbar.topLoc = 0;
    sbw->scrollbar.shownLength = sbw->scrollbar.min_thumb;
}

static void Realize (w, valueMask, attributes)
    Widget w;
    Mask *valueMask;
    XSetWindowAttributes *attributes;
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    XColor fore, back;
    
    if(sbw->simple.cursor_name == NULL)
	XtVaSetValues(w, XtNcursorName, "top_left_arrow", NULL);
    /* dont set the cursor of the window to anything */
    *valueMask &= ~CWCursor;
    /* 
     * The Simple widget actually stuffs the value in the valuemask. 
     */
    
    (*scrollbarWidgetClass->core_class.superclass->core_class.realize)
	(w, valueMask, attributes);
    
    /* Kludgy fix to cursor colors */
    fore.red = 0;
    fore.green = 0;
    fore.blue = 0;
    back.red = 0xffff;
    back.green = 0xffff;
    back.blue = 0xffff;
    XRecolorCursor(XtDisplay(w), sbw->simple.cursor, &fore, &back);
}

/* ARGSUSED */
static Boolean SetValues (current, request, desired, args, num_args)
    Widget  current,		/* what I am */
	    request,		/* what he wants me to be */
	    desired;		/* what I will become */
    ArgList args;
    Cardinal *num_args;
{
    ScrollbarWidget sbw = (ScrollbarWidget) current;
    ScrollbarWidget dsbw = (ScrollbarWidget) desired;
    Boolean redraw = FALSE;

/*
 * If these values are outside the acceptable range ignore them...
 */

    if (dsbw->scrollbar.top < 0.0 || dsbw->scrollbar.top > 1.0)
        dsbw->scrollbar.top = sbw->scrollbar.top;

    if (dsbw->scrollbar.shown < 0.0 || dsbw->scrollbar.shown > 1.0) 
        dsbw->scrollbar.shown = sbw->scrollbar.shown;

/*
 * Change colors and stuff...
 */
    if (XtIsRealized (desired)) {
	if (sbw->scrollbar.foreground != dsbw->scrollbar.foreground ||
	    sbw->core.background_pixel != dsbw->core.background_pixel ||
	    sbw->scrollbar.thumb != dsbw->scrollbar.thumb) {
	    XtReleaseGC (desired, sbw->scrollbar.gc);
	    CreateGC (desired);
	    redraw = TRUE;
	}
	if (sbw->scrollbar.top != dsbw->scrollbar.top ||
	    sbw->scrollbar.shown != dsbw->scrollbar.shown)
	    redraw = TRUE;
    }
    return redraw;
}

static void Resize (w)
    Widget w;
{
    /* ForgetGravity has taken care of background, but thumb may
     * have to move as a result of the new size. */
    SetDimensions ((ScrollbarWidget) w);
    Redisplay (w, (XEvent*) NULL, (Region)NULL);
}


/* ARGSUSED */
static void Redisplay (w, event, region)
    Widget w;
    XEvent *event;
    Region region;
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    int x, y;
    unsigned int width, height;

    if (sbw->scrollbar.orientation == XtorientHorizontal) {
	x = sbw->scrollbar.topLoc;
	y = 1;
	width = sbw->scrollbar.shownLength;
	height = sbw->core.height - 2;
    } else {
	x = 1;
	y = sbw->scrollbar.topLoc;
	width = sbw->core.width - 2;
	height = sbw->scrollbar.shownLength;
    }
    if (region == NULL ||
	XRectInRegion (region, x, y, width, height) != RectangleOut) {
	/* Forces entire thumb to be painted. */
	sbw->scrollbar.topLoc = -(sbw->scrollbar.length + 1);
    }
    PaintThumb (sbw, event);
    if (sbw->scrollbar.draw_arrows)
      PaintArrowButtons(sbw, event, FALSE, FALSE);
}


static Boolean CompareEvents (oldEvent, newEvent)
    XEvent *oldEvent, *newEvent;
{
#define Check(field) if (newEvent->field != oldEvent->field) return False;

    Check(xany.display);
    Check(xany.type);
    Check(xany.window);

    switch (newEvent->type) {
    case MotionNotify:
	Check(xmotion.state); 
	break;
    case ButtonPress:
    case ButtonRelease:
	Check(xbutton.state);
	Check(xbutton.button); 
	break;
    case KeyPress:
    case KeyRelease:
	Check(xkey.state);
	Check(xkey.keycode); 
	break;
    case EnterNotify:
    case LeaveNotify:
	Check(xcrossing.mode);
	Check(xcrossing.detail);
	Check(xcrossing.state); 
	break;
    }
#undef Check

    return True;
}

struct EventData {
    XEvent *oldEvent;
    int count;
};

static Bool PeekNotifyEvent (dpy, event, args)
    Display *dpy;
    XEvent *event;
    char *args;
{
    struct EventData *eventData = (struct EventData*)args;

    return ((++eventData->count == QLength(dpy)) /* since PeekIf blocks */
	    || CompareEvents(event, eventData->oldEvent));
}


static Boolean LookAhead (w, event)
    Widget w;
    XEvent *event;
{
    XEvent newEvent;
    struct EventData eventData;

    if (QLength (XtDisplay (w)) == 0) return False;

    eventData.count = 0;
    eventData.oldEvent = event;

    XPeekIfEvent (XtDisplay (w), &newEvent, PeekNotifyEvent, (char*)&eventData);

    return CompareEvents (event, &newEvent);
}


static void ExtractPosition (event, x, y)
    XEvent *event;
    Position *x, *y;		/* RETURN */
{
    switch( event->type ) {
    case MotionNotify:
	*x = event->xmotion.x;	 
	*y = event->xmotion.y;	  
	break;
    case ButtonPress:
    case ButtonRelease:
	*x = event->xbutton.x;   
	*y = event->xbutton.y;   
	break;
    case KeyPress:
    case KeyRelease:
	*x = event->xkey.x;      
	*y = event->xkey.y;	  
	break;
    case EnterNotify:
    case LeaveNotify:
	*x = event->xcrossing.x; 
	*y = event->xcrossing.y; 
	break;
    default:
	*x = 0; *y = 0;
    }
}

/* ARGSUSED */
static void HandleThumb (w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;		/* unused */
    Cardinal *num_params;	/* unused */
{
    Position x,y;
    ScrollbarWidget sbw = (ScrollbarWidget) w;

    ExtractPosition( event, &x, &y );
    /* if the motion event puts the pointer in thumb, call Move and Notify */
    /* also call Move and Notify if we're already in continuous scroll mode */
    if (sbw->scrollbar.scroll_mode == 2 ||
	(PICKLENGTH (sbw,x,y) >= sbw->scrollbar.topLoc &&
	PICKLENGTH (sbw,x,y) <= sbw->scrollbar.topLoc + sbw->scrollbar.shownLength)){
	XtCallActionProc(w, "MoveThumb", event, params, *num_params);
	XtCallActionProc(w, "NotifyThumb", event, params, *num_params);
    }
}

static void RepeatNotify (client_data, idp)
    XtPointer client_data;
    XtIntervalId *idp;
{
#define A_FEW_PIXELS 5
    ScrollbarWidget sbw = (ScrollbarWidget) client_data;
    int call_data;
    if (sbw->scrollbar.scroll_mode != 1 && sbw->scrollbar.scroll_mode != 3) {
	sbw->scrollbar.timer_id = (XtIntervalId) 0;
	return;
    }
    call_data = MAX (A_FEW_PIXELS, sbw->scrollbar.length / 20);
    if (sbw->scrollbar.scroll_mode == 1)
	call_data = -call_data;
    XtCallCallbacks((Widget)sbw, XtNscrollProc, (XtPointer) call_data);
    sbw->scrollbar.timer_id = 
    XtAppAddTimeOut(XtWidgetToApplicationContext((Widget)sbw),
		    (unsigned long) sbw->scrollbar.repeat_delay,
		    RepeatNotify,
		    client_data);
}


/*
 * Make sure the first number is within the range specified by the other
 * two numbers.
 */

static float FloatInRange(num, small, big)
    float num, small, big;
{
    return (num < small) ? small : ((num > big) ? big : num);
}


static void NotifyScroll (w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;		
    Cardinal *num_params;	
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    int call_data;
    Position x, y;
    Dimension bsize = (sbw->scrollbar.draw_arrows
		       ? (sbw->scrollbar.thickness)
		       : 0);
    
    if (sbw->scrollbar.scroll_mode == 2  /* if scroll continuous */
	|| LookAhead (w, event)) 
	return;

    ExtractPosition (event, &x, &y);
    if (sbw->scrollbar.shown >= 1.0) {
	return;
    }    
    if (sbw->scrollbar.orientation == XtorientHorizontal) {
	if (PICKLENGTH (sbw,x,y) < bsize) {
	    /* handle first arrow zone */
	    call_data = -MAX (A_FEW_PIXELS, sbw->scrollbar.length / 20);
	    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));
	    /* establish autoscroll */
	    sbw->scrollbar.timer_id = 
	      XtAppAddTimeOut (XtWidgetToApplicationContext (w),
			       (unsigned long)sbw->scrollbar.initial_delay,
			       RepeatNotify, (XtPointer)w);
	    sbw->scrollbar.scroll_mode = 1;
	    if (sbw->scrollbar.draw_arrows)
	      PaintArrowButtons(sbw, event, TRUE, -1);
	} else if (PICKLENGTH (sbw,x,y) < bsize*2) {
	    /* handle last arrow zone */
	    call_data = MAX (A_FEW_PIXELS, sbw->scrollbar.length / 20);
	    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));
	    /* establish autoscroll */
	    sbw->scrollbar.timer_id =
	      XtAppAddTimeOut (XtWidgetToApplicationContext (w), 
			       (unsigned long)sbw->scrollbar.initial_delay,
			       RepeatNotify, (XtPointer)w);
	    sbw->scrollbar.scroll_mode = 3;
	    if (sbw->scrollbar.draw_arrows)
	      PaintArrowButtons(sbw, event, -1, TRUE);
	} else if (PICKLENGTH (sbw, x, y) < sbw->scrollbar.topLoc) {
	    /* handle zone "above" the thumb */
	    call_data = - sbw->scrollbar.length;
	    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));
	} else if (PICKLENGTH (sbw, x, y) 
		   > sbw->scrollbar.topLoc + sbw->scrollbar.shownLength) {
	    /* handle zone "below" the thumb */
	    call_data = sbw->scrollbar.length;
	    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));
	} else {
	    /* handle the thumb in the motion notify action */
	}
    } else {
	if (PICKLENGTH (sbw,x,y) > (sbw->scrollbar.length-bsize)) {
	    /* handle last arrow zone */
	    call_data = MAX (A_FEW_PIXELS, sbw->scrollbar.length / 20);
	    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));
	    /* establish autoscroll */
	    sbw->scrollbar.timer_id =
	      XtAppAddTimeOut (XtWidgetToApplicationContext (w), 
			       (unsigned long) sbw->scrollbar.initial_delay,
			       RepeatNotify, (XtPointer)w);
	    sbw->scrollbar.scroll_mode = 3;
	    if (sbw->scrollbar.draw_arrows)
	      PaintArrowButtons(sbw, event, -1, TRUE);
	} else if (PICKLENGTH (sbw,x,y) > (sbw->scrollbar.length-bsize*2)) {
	    /* handle first arrow zone */
	    call_data = -MAX (A_FEW_PIXELS, sbw->scrollbar.length / 20);
	    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));
	    /* establish autoscroll */
	    sbw->scrollbar.timer_id = 
	      XtAppAddTimeOut (XtWidgetToApplicationContext (w),
			       (unsigned long) sbw->scrollbar.initial_delay,
			       RepeatNotify, (XtPointer)w);
	    sbw->scrollbar.scroll_mode = 1;
	    if (sbw->scrollbar.draw_arrows)
	      PaintArrowButtons(sbw, event, TRUE, -1);
	} else if (PICKLENGTH (sbw, x, y) 
		   > sbw->scrollbar.topLoc + sbw->scrollbar.shownLength) {
	    /* handle zone "below" the thumb */
	    call_data = sbw->scrollbar.length;
	    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));
	} else if (PICKLENGTH (sbw, x, y) < sbw->scrollbar.topLoc) {
	    /* handle zone "above" the thumb */
	    call_data = - sbw->scrollbar.length;
	    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));	    
	} else 
	{
	    /* handle the thumb in the motion notify action */
	}
    }

    return;
}

static void ScrollOneLineUp (w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    int call_data;

    if (sbw->scrollbar.scroll_mode == 2  /* if scroll continuous */
	|| LookAhead (w, event))
	return;

    if (sbw->scrollbar.shown >= 1.0) {
	return;
    }
    call_data = -MAX (A_FEW_PIXELS, sbw->scrollbar.length / 20);
    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));

    return;
}

static void ScrollPageUp (w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    int call_data;

    if (sbw->scrollbar.scroll_mode == 2  /* if scroll continuous */
	|| LookAhead (w, event))
	return;

    if (sbw->scrollbar.shown >= 1.0) {
	return;
    }
    call_data = - sbw->scrollbar.length;
    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));

    return;
}

static void ScrollOneLineDown (w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    int call_data;

    if (sbw->scrollbar.scroll_mode == 2  /* if scroll continuous */
	|| LookAhead (w, event))
	return;

    if (sbw->scrollbar.shown >= 1.0) {
	return;
    }
    call_data = MAX (A_FEW_PIXELS, sbw->scrollbar.length / 20);
    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));

    return;
}

static void ScrollPageDown (w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    int call_data;

    if (sbw->scrollbar.scroll_mode == 2  /* if scroll continuous */
	|| LookAhead (w, event))
	return;

    if (sbw->scrollbar.shown >= 1.0) {
	return;
    }
    call_data = sbw->scrollbar.length;
    XtCallCallbacks (w, XtNscrollProc, (XtPointer)(call_data));

    return;
}

/* ARGSUSED */
static void EndScroll(w, event, params, num_params )
    Widget w;
    XEvent *event;		/* unused */
    String *params;		/* unused */
    Cardinal *num_params;	/* unused */
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;

    sbw->scrollbar.scroll_mode = 0;
    /* no need to remove any autoscroll timeout; it will no-op */
    /* because the scroll_mode is 0 */
    /* but be sure to remove timeout in destroy proc */
    if (sbw->scrollbar.draw_arrows)
      PaintArrowButtons(sbw, event, FALSE, FALSE);
}

static float FractionLoc (sbw, x, y)
    ScrollbarWidget sbw;
    int x, y;
{
    float   result;
    int margin;
    float   height, width;

    margin = MARGIN (sbw);
    x -= margin*2;
    y -= 1;
    height = sbw->core.height - 2 * margin;
    width = sbw->core.width - 2 * margin;
    result = PICKLENGTH (sbw, x / width, y / height);
    return FloatInRange(result, 0.0, 1.0);
}


static void MoveThumb (w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;		/* unused */
    Cardinal *num_params;	/* unused */
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;
    Position x, y;
    float loc, t, s;

    if (LookAhead (w, event)) return;

    if (!event->xmotion.same_screen) return;

    ExtractPosition (event, &x, &y);
    loc = FractionLoc (sbw, x, y);
    t = sbw->scrollbar.top;
    s = sbw->scrollbar.shown;
    if (sbw->scrollbar.scroll_mode != 2 )
      /* initialize picked position */
      sbw->scrollbar.picked = (FloatInRange( loc, t, t + s ) - t);
    if (sbw->scrollbar.pick_top)
      sbw->scrollbar.top = loc;
    else {
      sbw->scrollbar.top = loc - sbw->scrollbar.picked;
      if (sbw->scrollbar.top < 0.0) sbw->scrollbar.top = 0.0;
    }
#if 0
    /*
    Date: 04 Dec 1999 22:20:52 -0500
    From: "Stefan Monnier <foo@acm.com>"
	<monnier+comp/windows/x/intrinsics/news/@tequila.cs.yale.edu>
    Newsgroups: comp.windows.x.intrinsics
    Subject: annoying bug in Xaw3d


    Xaw3d (at least version 1.3) has the nasty habit of ignoring
    XawScrollbarSetThumb requests while dragging the thumb.
    It also has the annoying idea of preventing the application from
    moving the thumb past `1.0 - scrollbar.shown' (i.e. prevent
    it from shrinking at the end) which might be OK for several applications
    but not for programs like Emacs where the shrinking at the end
    is exactly what we want.

    Working around those two restrictions is a severe pain in the ass
    and I have no idea why this code was added in the first place.

    In any case, I've been using the patch below for some time now without
    observing any undesirable behavior.  I have the strong impression
    that such behavior will not appear since the patch makes Xaw3d
    behave more like Xaw (what programs expect).

    Without this patch, Emacs' scrollbar (when using Xaw-style scrollbars)
    behaves very poorly when reaching the end of the buffer although
    I've already done my best to add kludges to Emacs to work around
    the problem.

    This problem probably appears in most Xaw3d derivatives.
    */
    /* don't allow scrollbar to shrink at end */
    if (sbw->scrollbar.top + sbw->scrollbar.shown > 1.0)
      sbw->scrollbar.top = 1.0 - sbw->scrollbar.shown;
#endif
    sbw->scrollbar.scroll_mode = 2; /* indicate continuous scroll */
    PaintThumb (sbw, event);
    XFlush (XtDisplay (w));	/* re-draw it before Notifying */
}


/* ARGSUSED */
static void NotifyThumb (w, event, params, num_params )
    Widget w;
    XEvent *event;
    String *params;		/* unused */
    Cardinal *num_params;	/* unused */
{
    register ScrollbarWidget sbw = (ScrollbarWidget) w;
    float top = sbw->scrollbar.top;

    if (LookAhead (w, event)) return;

    /* thumbProc is not pretty, but is necessary for backwards
       compatibility on those architectures for which it work{s,ed};
       the intent is to pass a (truncated) float by value. */
    
    /* This corrects for rounding errors: If the thumb is moved to the end of
       the scrollable area sometimes the last line/column is not displayed.
       This can happen when the integer number of the top line or leftmost
       column to be be displayed is calculated from the float value
       sbw->scrollbar.top. The numerical error of this rounding problem is
       very small. We therefore add a small value which then forces the
       next line/column (the correct one) to be used. Since we can expect
       that the resolution of display screens will not be higher then
       10000 text lines/columns we add 1/10000 to the top position. The
       intermediate variable `top' is used to avoid erroneous summing up
       corrections (can this happen at all?). If the arrows are not displayed
       there is no problem since in this case there is always a constant
       integer number of pixels the thumb must be moved in order to scroll
       to the next line/column. */
    top += 0.0001;

    XtCallCallbacks (w, XtNthumbProc, *(XtPointer*)&top);
    XtCallCallbacks (w, XtNjumpProc, (XtPointer)&top);
}



/************************************************************
 *
 *  Public routines. 
 *
 ************************************************************/

/* Set the scroll bar to the given location. */

#if NeedFunctionPrototypes
void XawScrollbarSetThumb (Widget w, 
#if NeedWidePrototypes
			double top, double shown)
#else
			float top, float shown)
#endif
#else
void XawScrollbarSetThumb (w, top, shown)
    Widget w;
    float top, shown;
#endif
{
    ScrollbarWidget sbw = (ScrollbarWidget) w;

#ifdef WIERD
    fprintf(stderr,"< XawScrollbarSetThumb w=%p, top=%f, shown=%f\n", 
	    w,top,shown);
#endif
#if 0
    /* see comments above */
    if (sbw->scrollbar.scroll_mode == (char) 2) return; /* if still thumbing */
#endif
    sbw->scrollbar.top = (top > 1.0) ? 1.0 :
				(top >= 0.0) ? top : sbw->scrollbar.top;

    sbw->scrollbar.shown = (shown > 1.0) ? 1.0 :
				(shown >= 0.0) ? shown : sbw->scrollbar.shown;

    PaintThumb (sbw);
}

