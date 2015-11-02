
/*

Copyright (c) 1994  X Consortium

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

#ifndef XawTraversal_h
#define XawTraversal_h

#define XtNfocusPolicy		"focusPolicy"
#define XtCFocusPolicy		"FocusPolicy"


typedef	enum {
	  XawFocusExplicit,	/* focus changed only by keyboard or click */
	  XawFocusPointer,	/* focus also changed by pointer motion */
	  XawFocusOld		/* focus only changed by pointer motion */
	} XawFocusPolicy ;


	/* This function allows non-Athena widgets to join the
	 * focus protocol.  Call it once per application context.
	 */

extern	void	XawFocusInstallActions(
#if NeedFunctionPrototypes
    XtAppContext
#endif
) ;

	/* This function can be called to help connect non-Athena widgets
	 * to the focus protocol.  It installs new translations and
	 * actions into the target widget:
	 *
	 *	<EnterWindow>:	XawFocusEnterWindow()
	 *	<LeaveWindow>:	XawFocusLeaveWindow()
	 *	Shift<Key>Tab:	XawFocusPrevious()
	 *	<Key>Tab:	XawFocusNext()
	 *	<Key>Home:	XawFocusHome()
	 *	<Key>End:	XawFocusEnd()
	 *	<Key>Up:	XawFocusPreviousGroup()
	 *	<Key>Down:	XawFocusNextGroup()
	 *	<Key>KP_Home:	XawFocusHome()
	 *	<Key>KP_End:	XawFocusEnd()
	 *	<Key>KP_Up:	XawFocusPreviousGroup()
	 *	<Key>KP_Down:	XawFocusNextGroup()
	 *
	 * Set 'override' to True to override translations, else False
	 * to augment.
	 *
	 * Note: this doesn't always do the whole job.  Since this
	 * function overrides the <EnterWindow> and <LeaveWindow>
	 * events, it may override actions you needed.  If so,
	 * your application should follow this call with code to
	 * reset <EnterWindow> and <LeaveWindow> to what you want.
	 *
	 * Note that XawFocusEnterWindow() and XawFocusLeaveWindow()
	 * will result in calls to <FocusIn> and <FocusOut>.
	 *
	 * Here is an example:  Suppose widget Foo has this
	 * translation table:
	 *
	 *	<EnterWindow>:	highlight()
	 *	<LeaveWindow>:	unhighlight()
	 *	<FocusIn>:	highlight()
	 *	<FocusOut>:	unhighlight()
	 *
	 * In this case, the <EnterWindow> and <LeaveWindow> actions
	 * will be replaced with XawFocusEnterWindow(), XawFocusLeaveWindow().
	 * These will result in calls to <FocusIn> and <FocusOut> which
	 * will do the right things.
	 *
	 * Suppose widget Foo has this translation table:
	 *
	 *	<EnterWindow>:	highlight()
	 *	<LeaveWindow>:	unhighlight()
	 *
	 * A call to XawFocusInstall() will override these actions,
	 * causing your widget to no longer highlight properly.  The
	 * best solution is to add <FocusIn> and <FocusOut> to Foo's
	 * translation table.
	 *
	 * Suppose Foo has this translation table:
	 *
	 *	<EnterWindow>:	highlight() start-animating()
	 *	<LeaveWindow>:	unhighlight() stop-animating()
	 *	<FocusIn>:	highlight()
	 *	<FocusOut>:	unhighlight()
	 *
	 * The best solution here is to call XawOverrideTranslations()
	 * after XawFocusInstall(), and override with these translations:
	 *
	 *	<EnterWindow>:	XawFocusEnterWindow() start-animating()
	 *	<LeaveWindow>:	XawFocusLeaveWindow() stop-animating()
	 *
	 */

extern	void	XawFocusInstall(
#if NeedFunctionPrototypes
    Widget, Bool override
#endif
);



	/* These functions may be called to explicitly modify focus. */


#if NeedFunctionPrototypes
extern	void	XawFocusNext(Widget w, Time tm) ;
extern	void	XawFocusNextGroup(Widget w, Time tm) ;
extern	void	XawFocusPrevious(Widget w, Time tm) ;
extern	void	XawFocusPreviousGroup(Widget w, Time tm) ;
extern	void	XawFocusHome(Widget w, Time tm) ;
extern	void	XawFocusHomeGroup(Widget w, Time tm) ;
extern	void	XawFocusEnd(Widget w, Time tm) ;
extern	void	XawFocusEndGroup(Widget w, Time tm) ;
extern	void	XawFocusTake(Widget w, Time tm) ;
extern	void	XawFocusEnterWindow(Widget w, XawFocusPolicy p, Time tm) ;
extern	void	XawFocusLeaveWindow(Widget w, XawFocusPolicy p, Time tm) ;
#else
extern	void	XawFocusNext() ;
extern	void	XawFocusNextGroup() ;
extern	void	XawFocusPrevious() ;
extern	void	XawFocusPreviousGroup() ;
extern	void	XawFocusHome() ;
extern	void	XawFocusHomeGroup() ;
extern	void	XawFocusEnd() ;
extern	void	XawFocusEndGroup() ;
extern	void	XawFocusTake() ;
extern	void	XawFocusEnterWindow() ;
extern	void	XawFocusLeaveWindow() ;
#endif


#endif	/* XawTraversal_h */
