/*
 * $Id: Traversal.c,v 1.2 2000/10/12 14:55:20 ulric Exp $
 */


/*

Copyright (c) 1999  X Consortium

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

*/

/*  ___________________________________________________________________
 * /\                                                                  \
 * \_| This code implements keyboard traversal for the Athena widgets. |
 *   |   ______________________________________________________________|_
 *    \_/_______________________________________________________________/
 */




#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/Xmu/CharSet.h>
#include "TraversalP.h"
#include <stdio.h>



static	XawFocusPolicy	policy = XawFocusPointer ;


static	Time	getEventTime(XEvent *event) ;


static	char	focusTransTab[] =
"   <EnterWindow>:	XawFocusEnterWindow()\n"
"   <LeaveWindow>:	XawFocusLeaveWindow()\n"
"   Shift<Key>Tab:	XawFocusPrevious()\n"
"   <Key>Tab:		XawFocusNext()\n"
"   <Key>Home:		XawFocusHome()\n"
"   <Key>KP_Home:	XawFocusHome()\n"
"   <Key>End:		XawFocusEnd()\n"
"   <Key>KP_End:	XawFocusEnd()\n"
"   <Key>Up:		XawFocusPreviousGroup()\n"
"   <Key>KP_Up:		XawFocusPreviousGroup()\n"
"   <Key>Down:		XawFocusNextGroup()\n"
"   <Key>KP_Down:	XawFocusNextGroup()\n";
static	XtTranslations	focusTrans ;
static	Bool		focusInited = False ;

static	XtActionsRec	focusActions[] = {
  {"XawFocusNext", XawFocusNextAction},
  {"XawFocusPrevious", XawFocusPreviousAction},
  {"XawFocusHome", XawFocusHomeAction},
  {"XawFocusEnd", XawFocusEndAction},
  {"XawFocusNextGroup", XawFocusNextGroupAction},
  {"XawFocusPreviousGroup", XawFocusPreviousGroupAction},
  {"XawFocusHomeGroup", XawFocusHomeGroupAction},
  {"XawFocusEndGroup", XawFocusEndGroupAction},
  {"XawFocusTake", XawFocusTakeAction},
  {"XawFocusEnterWindow", XawFocusEnterWindowAction},
  {"XawFocusLeaveWindow", XawFocusLeaveWindowAction}
} ;




void
XawFocusInstallActions(XtAppContext ctx)
{
	XtAppAddActions(ctx, focusActions, XtNumber(focusActions));
}



void
XawFocusInstall(Widget w, Bool override)
{
	if( !focusInited ) {
	  focusTrans = XtParseTranslationTable(focusTransTab) ;
	  focusInited = True ;
	}
	if( override )
	  XtOverrideTranslations(w, focusTrans) ;
	else
	  XtAugmentTranslations(w, focusTrans) ;
}


static	Bool
isViewable(dpy, w)
    Display	*dpy ;
    Window	w ;
{
    XWindowAttributes atts ;

    if( !XGetWindowAttributes(dpy, w, &atts) ) return False ;
    else return atts.map_state == IsViewable ;
}


Boolean
XawAcceptFocus( Widget w, Time *tm )
{
    /* To be eligible for keyboard focus, the widget must be
     * realized, sensitive, managed, and be viewable.
     */

    /* Unfortunately, it requires a round trip to the server
     * to find out if a window is viewable.
     */

    if( !w->core.being_destroyed  && XtIsRealized(w) &&
	XtIsSensitive(w) && w->core.visible && XtIsManaged(w)  &&
	isViewable(XtDisplay(w), XtWindow(w)) )
    {
      XSetInputFocus(XtDisplay(w), XtWindow(w), RevertToParent,
	tm != NULL ? *tm : CurrentTime );
      return True ;
    }
    else
      return False ;
}


void
XawFocusNextAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusNext(w, tm) ;
}



void
XawFocusPreviousAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusPrevious(w, tm) ;
}



void
XawFocusHomeAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	(void) XawFocusHome(w, tm) ;
}



void
XawFocusEndAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	(void) XawFocusEnd(w, tm) ;
}



void
XawFocusNextGroupAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusNextGroup(w, tm) ;
}



void
XawFocusPreviousGroupAction(Widget w, XEvent *event,
	String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusPreviousGroup(w, tm) ;
}



void
XawFocusHomeGroupAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusHomeGroup(w, tm) ;
}



void
XawFocusEndGroupAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusEndGroup(w, tm) ;
}



void
XawFocusTakeAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusTake(w, tm) ;
}



void
XawFocusEnterWindowAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusEnterWindow(w, policy, tm) ;
}



void
XawFocusLeaveWindowAction(Widget w, XEvent *event, String *params, Cardinal *np)
{
	Time	tm = getEventTime(event) ;

	/* TODO: get policy from resources */

	if( policy == XawFocusOld ) {
	  XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm) ;
	  return ;
	}

	XawFocusLeaveWindow(w, policy, tm) ;
}


	/* end of the action procs */




#define	lastCh(w)	((w)->composite.num_children - 1)

static	Time
getEventTime(event)
	XEvent	*event ;
{
	Time	tm = CurrentTime ;

	if( event != NULL ) {
	  switch( event->type ) {
	    case ButtonPress:
	    case ButtonRelease: tm = event->xbutton.time ; break ;
	    case KeyPress:
	    case KeyRelease: tm = event->xkey.time ; break ;
	    case MotionNotify: tm = event->xmotion.time ; break ;
	    case EnterNotify:
	    case LeaveNotify: tm = event->xcrossing.time ; break ;
	  }
	}

	return tm ;
}




	/* Utility: search for widget in it's parent's child list,
	 * return the index.
	 */

static	int
findInParent(w)
	Widget	w ;
{
	CompositeWidget p = (CompositeWidget) XtParent(w) ;
	int	i ;

	if( p == NULL )
	  return -1 ;

	for(i=0; i < p->composite.num_children; ++i)
	  if( p->composite.children[i] == w )
	    return i ;

	return -1 ;
}




	/* utility: search composite widget w, starting at c, for
	 * a child widget willing to accept input.  Direction is
	 * either +1 or -1 for forward/backward search.
	 */


static	Bool
focusFind(w, c, recursive, direction, tm)
	CompositeWidget	w ;
	int	c ;
	Bool	recursive ;
	int	direction ;
	Time	tm ;
{
	int	nc ;
	Widget	cw ;

	nc = w->composite.num_children ;

	while( c >= 0 && c < nc )
	{
	  cw = w->composite.children[c] ;
	  if( XtIsManaged(cw) )
	  {
	    if( XtCallAcceptFocus(cw, &tm) )
	      return True ;
	    if( recursive && XtIsComposite(cw) )
	    {
	      CompositeWidget cwc = (CompositeWidget)cw ;
	      int c0 = direction > 0 ? 0 : lastCh(cwc) ;
	      if( focusFind(cwc, c0, recursive, direction, tm) )
		return True ;
	    }
	  }
	  c += direction ;
	}

	return False ;	/* nobody wanted it */
}




void
XawFocusNext(w, tm)
	Widget	w ;
	Time	tm ;
{
	Widget	p ;
	int	ci ;

	/* Search for the next widget after this one to
	 * receive input.  If we encounter a composite widget,
	 * set focus to its first willing child, if any.  If we
	 * reach the end, pop up a level and keep trying.  If we
	 * can't pop up, go to the start.
	 */

	/* First, see if this is a composite widget; test children. */

	if( XtIsComposite(w) &&
	    focusFind((CompositeWidget) w, 0, True, +1, tm) )
	  return ;

	/* Nope.  Start searching siblings.  Easiest way to do this
	 * is to search parent.
	 */

	while( (p = XtParent(w)) != NULL && !XtIsShell(p) )
	{
	  if( (ci = findInParent(w)) == -1 )
	    return ;

	  if( focusFind((CompositeWidget)p, ci+1, True, +1, tm) )
	    return ;

	  /* No luck there; pop up a level and try again */
	  w = p ;
	}

	/* Made it all the way to the top.  Start from the beginning */
	XawFocusHome(w, tm) ;
}


	/* Utility: search parents until a parent with multiple children
	 * is found.
	 */

static	CompositeWidget
getMultiParent(w)
	Widget	w ;
{
	CompositeWidget p ;
	while( (p = (CompositeWidget)XtParent(w)) != NULL &&
		!XtIsShell((Widget)p)  &&
		p->composite.num_children == 1 )
	    w = (Widget)p ;
	return p ;
}

void
XawFocusNextGroup(w, tm)
	Widget	w ;
	Time	tm ;
{
	CompositeWidget p = getMultiParent(w) ;
	int	ci ;

	/* search this widget's parent for another widget eligible
	 * to receive input.
	 *
	 * Actually, if the parent has only this one child, tabbing
	 * isn't very interesting, so we search up until we find
	 * a multi-child parent.
	 */

	if( p == NULL )
	  return ;

	if( (ci = findInParent(w)) != -1 )
	{
	  if( focusFind(p, ci+1, False, +1, tm) )
	    return ;
	  if( focusFind(p, 0, False, +1, tm) )
	    return ;
	}
	/* nobody wanted it, just return */
}


void
XawFocusPrevious(w, tm)
	Widget	w ;
	Time	tm ;
{
	Widget	p ;
	int	ci ;

	/* see focusNext() for detailed comments */

	while( (p =  XtParent(w)) != NULL && !XtIsShell(p) )
	{
	  if( (ci = findInParent(w)) == -1 ) return ;
	  if( focusFind((CompositeWidget)p, ci-1, True, -1, tm) ) return ;
	  w = (Widget)p ;
	}
	XawFocusEnd(w, tm) ;
}

void
XawFocusPreviousGroup(w, tm)
	Widget	w ;
	Time	tm ;
{
	CompositeWidget p = getMultiParent(w) ;
	int	ci ;

	if( p == NULL ) return ;

	if( (ci = findInParent(w)) != -1 )
	{
	  if( focusFind(p, ci-1, False, -1, tm) ) return ;
	  if( focusFind(p, lastCh(p), False, -1, tm) ) return ;
	}
}

void
XawFocusHome(w, tm)
	Widget	w ;
	Time	tm ;
{
	Widget	p ;

	/* Climb up to the top-level widget and then start
	 * searching from there.
	 */

	while( (p = XtParent(w)) != NULL && !XtIsShell(p) )
	  w = p ;

	(void) focusFind((CompositeWidget) w, 0, True, +1, tm) ;
}

void
XawFocusHomeGroup(w, tm)
	Widget	w ;
	Time	tm ;
{
	CompositeWidget p = getMultiParent(w) ;

	if( p != NULL )
	  (void) focusFind((CompositeWidget) p, 0, True, +1, tm) ;
}

void
XawFocusEnd(w, tm)
	Widget	w ;
	Time	tm ;
{
	Widget	p ;

	while( (p = XtParent(w)) != NULL && !XtIsShell(p) )
	  w = p ;

	(void) focusFind((CompositeWidget) w,
		lastCh(((CompositeWidget)w)),
		True, -1, tm) ;
}

void
XawFocusEndGroup(w, tm)
	Widget	w ;
	Time	tm ;
{
	CompositeWidget p = getMultiParent(w) ;

	if( p != NULL )
	  (void) focusFind((CompositeWidget) w,
		lastCh(((CompositeWidget)w)),
		True, -1, tm) ;
}

void
XawFocusTake(w, tm)
	Widget	w ;
	Time	tm ;
{
	(void) XtCallAcceptFocus(w, &tm) ;
}

void
XawFocusEnterWindow(w, policy, tm)
	Widget	w ;
	XawFocusPolicy policy ;
	Time	tm ;
{
	switch( policy ) {
	  case XawFocusExplicit: break ;
	  case XawFocusPointer:
	  case XawFocusOld:
	    XawFocusTake(w, tm) ;
	    break ;
	}
}

void
XawFocusLeaveWindow(w, policy, tm)
	Widget	w ;
	XawFocusPolicy policy ;
	Time	tm ;
{
	Window current;
	int revert;
	XGetInputFocus(XtDisplay(w), &current, &revert);
	if (XtWindow(w) != current) {
		switch( policy ) {
		  case XawFocusExplicit: break ;
		  case XawFocusPointer:
		  case XawFocusOld:
		    XSetInputFocus(XtDisplay(w), PointerRoot, RevertToPointerRoot, tm);
		    break ;
		}
	}
}

