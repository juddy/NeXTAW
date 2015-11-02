/* $XConsortium: MenuButton.c,v 1.21 95/06/26 20:35:12 kaleb Exp $ */
/* MODIFIED FOR N*XTSTEP LOOK	 				*/
/* Modifications Copyright (c) 1996, 1997 by Alfredo Kojima	*/

/*
Copyright (c) 1989, 1994  X Consortium

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
 *
 */

/* $XFree86: xc/lib/Xaw/MenuButton.c,v 3.0.6.2 1998/05/20 05:06:17 dawes Exp $ */

/***********************************************************************
 *
 * MenuButton Widget
 *
 ***********************************************************************/

/*
 * MenuButton.c - Source code for MenuButton widget.
 *
 * This is the source code for the Athena MenuButton widget.
 * It is intended to provide an easy method of activating pulldown menus.
 *
 * Date:    May 2, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

#include <stdio.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#ifdef HAS_XMU_H
#include <X11/Xmu/Xmu.h>
#endif

#include "XawInit.h"
#include "MenuButtoP.h"

#include "XawAlloc.h"

static void ClassInitialize(), Initialize();
static void PopupMenu();
static void Redisplay();

#define INDICATOR_SPACE 13

#define superclass ((CommandWidgetClass)&commandClassRec)

static char defaultTranslations[] = 
/*"<EnterWindow>: highlight()\n\
 <LeaveWindow>: reset()\n\
 Any<BtnDown>:  reset() PopupMenu()";*/
 "Any<BtnDown>:  PopupMenu()";

/****************************************************************
 *
 * Full class record constant
 *
 ****************************************************************/

/* Private Data */

#define offset(field) XtOffsetOf(MenuButtonRec, field)
static XtResource resources[] = {
  {
    XtNmenuName, XtCMenuName, XtRString, sizeof(String), 
    offset(menu_button.menu_name), XtRString, (XtPointer)"menu"},
      
   {XtNmenuButtonStyle, XtCMenuButtonStyle, XtRMenuButtonStyle, 
	 sizeof(XtMenuButtonStyle), offset(menu_button.menubutton_style), 
	 XtRMenuButtonStyle, (XtPointer)XtMenuButtonSimple},
};
#undef offset

static XtActionsRec actionsList[] =
{
  {"PopupMenu",	PopupMenu}
};

MenuButtonClassRec menuButtonClassRec = {
  {
    (WidgetClass) superclass,		/* superclass		  */	
    "MenuButton",			/* class_name		  */
    sizeof(MenuButtonRec),       	/* size			  */
    ClassInitialize,			/* class_initialize	  */
    NULL,				/* class_part_initialize  */
    FALSE,				/* class_inited		  */
    Initialize,				/* initialize		  */
    NULL,				/* initialize_hook	  */
    XtInheritRealize,			/* realize		  */
    actionsList,			/* actions		  */
    XtNumber(actionsList),		/* num_actions		  */
    resources,				/* resources		  */
    XtNumber(resources),		/* resource_count	  */
    NULLQUARK,				/* xrm_class		  */
    FALSE,				/* compress_motion	  */
    TRUE,				/* compress_exposure	  */
    TRUE,				/* compress_enterleave    */
    FALSE,				/* visible_interest	  */
    NULL,				/* destroy		  */
    XtInheritResize,			/* resize		  */
    Redisplay,				/* expose		  */
    NULL,				/* set_values		  */
    NULL,				/* set_values_hook	  */
    XtInheritSetValuesAlmost,		/* set_values_almost	  */
    NULL,				/* get_values_hook	  */
    NULL,				/* accept_focus		  */
    XtVersion,				/* version		  */
    NULL,				/* callback_private	  */
    defaultTranslations,               	/* tm_table		  */
    XtInheritQueryGeometry,		/* query_geometry	  */
    XtInheritDisplayAccelerator,	/* display_accelerator	  */
    NULL				/* extension		  */
  },  /* CoreClass fields initialization */
  {
    XtInheritChangeSensitive		/* change_sensitive	  */ 
  },  /* SimpleClass fields initialization */
  {
    XtInheritXaw3dShadowDraw           /* shadowdraw           */
  },  /* ThreeDClass fields initialization */
  {
    0,                                     /* field not used    */
  },  /* LabelClass fields initialization */
  {
    0,                                     /* field not used    */
  },  /* CommandClass fields initialization */
  {
    0,                                     /* field not used    */
  }  /* MenuButtonClass fields initialization */
};

  /* for public consumption */
WidgetClass menuButtonWidgetClass = (WidgetClass) &menuButtonClassRec;

/****************************************************************
 *
 * Private Procedures
 *
 ****************************************************************/

static XrmQuark	XtQMenuButtonSimple, XtQMenuButtonSelect, XtQMenuButtonAction;

#define	done(address, type) \
	{ toVal->size = sizeof(type); \
	  toVal->addr = (XPointer) address; \
	  return; \
	}

/* ARGSUSED */
static void _CvtStringToMenuButtonStyle(args, num_args, fromVal, toVal)
    XrmValuePtr args;		/* unused */
    Cardinal    *num_args;      /* unused */
    XrmValuePtr fromVal;
    XrmValuePtr toVal;
{
    static XtMenuButtonStyle mbStyle;
    XrmQuark q;
    char lowerName[1000];

    XmuCopyISOLatin1Lowered (lowerName, (char*)fromVal->addr);
    q = XrmStringToQuark(lowerName);
    if (q == XtQMenuButtonSimple) {
	mbStyle = XtMenuButtonSimple;
	done(&mbStyle, XtMenuButtonStyle);
    }
    if (q == XtQMenuButtonAction) {
	mbStyle = XtMenuButtonAction;
	done(&mbStyle, XtMenuButtonStyle);
    }
    if (q == XtQMenuButtonSelect) {
	mbStyle = XtMenuButtonSelect;
	done(&mbStyle, XtMenuButtonStyle);
    }
    XtStringConversionWarning(fromVal->addr, "menuButtonStyle");
    toVal->addr = NULL;
    toVal->size = 0;
}


static void ClassInitialize()
{
    XawInitializeWidgetSet();
    XtQMenuButtonSimple = XrmPermStringToQuark("simple");
    XtQMenuButtonAction = XrmPermStringToQuark("action");
    XtQMenuButtonSelect = XrmPermStringToQuark("select");

    XtAddConverter( XtRString, XtRMenuButtonStyle, _CvtStringToMenuButtonStyle,
		    (XtConvertArgList)NULL, 0 );
    
    XtRegisterGrabAction(PopupMenu, True, 
			 (unsigned int)(ButtonPressMask | ButtonReleaseMask),
			 GrabModeAsync, GrabModeAsync);
}


/*ARGSUSED*/
static void Initialize(request, new, args, num_args)
 Widget request, new;
 ArgList args;
 Cardinal *num_args;
{
    MenuButtonWidget mbw = (MenuButtonWidget) new;
    
    if (mbw->menu_button.menubutton_style!=XtMenuButtonSimple) {
	/* if we'll use an indicator */
	XtResizeWidget(new, mbw->core.width + INDICATOR_SPACE, mbw->core.height,
		       mbw->core.border_width);
    }
}


/*ARGSUSED*/
static void
Redisplay(w, event, region)
Widget w;
XEvent *event;
Region region;
{
    MenuButtonWidget mbw = (MenuButtonWidget) w;
    Dimension	s = mbw->threeD.shadow_width;
    GC light2 = mbw->threeD.top_shadow_GC;
    GC light = mbw->threeD.top_half_shadow_GC;
    GC dark2 = mbw->threeD.bot_shadow_GC;      
    GC dark = mbw->threeD.bot_half_shadow_GC;
    Display *dpy = XtDisplay(w);
    Window win = XtWindow(w);
    int x, y;

    x = w->core.width - INDICATOR_SPACE - s;
    y = (w->core.height - 8)/2;

    switch (mbw->menu_button.menubutton_style) {
     case XtMenuButtonSelect:
	mbw->label.label_width -= INDICATOR_SPACE;
	(*superclass->core_class.expose) (w, event, region);
	mbw->label.label_width += INDICATOR_SPACE;
	
	XFillRectangle(dpy, win, dark2, x+2, y+2, 9, 6);
	XDrawLine(dpy, win, light, x, y, x+8, y);
	XDrawLine(dpy, win, light, x, y, x, y+5);
	XDrawLine(dpy, win, dark, x, y+5, x+8, y+5);
	XDrawLine(dpy, win, dark, x+8, y, x+8, y+5);
	
	XFillRectangle(dpy, win, light2, x+1, y+1, 6, 3);
	XDrawLine(dpy, win, dark2, x+1, y+4, x+7, y+4);
	XDrawLine(dpy, win, dark2, x+7, y+1, x+7, y+4);
	break;
	
     case XtMenuButtonAction:
	mbw->label.label_width -= INDICATOR_SPACE;
	(*superclass->core_class.expose) (w, event, region);
	mbw->label.label_width += INDICATOR_SPACE;
	
	XDrawLine(dpy, win, dark2, x, y+1, x+3, y+6);
	XDrawLine(dpy, win, light, x+7, y+1, x+4, y+7);
	XDrawLine(dpy, win, dark, x, y, x+7, y);
	break;

     default:
	mbw->label.label_width -= INDICATOR_SPACE;
	(*superclass->core_class.expose) (w, event, region);
	mbw->label.label_width += INDICATOR_SPACE;
    }    
}

    
/* ARGSUSED */
static void
PopupMenu(w, event, params, num_params)
Widget w;
XEvent * event;
String * params;
Cardinal * num_params;
{
  MenuButtonWidget mbw = (MenuButtonWidget) w;
  Widget menu = NULL, temp;
  Arg arglist[2];
  Cardinal num_args;
  int menu_x, menu_y, menu_width, menu_height, button_height;
  Position button_x, button_y;

  temp = w;
  while(temp != NULL) {
    menu = XtNameToWidget(temp, mbw->menu_button.menu_name);
    if (menu == NULL) 
      temp = XtParent(temp);
    else
      break;
  }

  if (menu == NULL) {
    char error_buf[BUFSIZ];
    char *err1 = "MenuButton: Could not find menu widget named ";
    char *perr;
    int len;

    len = strlen(err1) + strlen(mbw->menu_button.menu_name) + 1 + 1;
    perr = XtStackAlloc(len, error_buf);
    if (perr == NULL) return;
    sprintf(perr, "%s%s.", err1, mbw->menu_button.menu_name);
    XtAppWarning(XtWidgetToApplicationContext(w), perr);
    XtStackFree(perr, error_buf);
    return;
  }
  if (!XtIsRealized(menu))
      XtRealizeWidget(menu);
  
  menu_width = menu->core.width + 2 * menu->core.border_width;
    /*
  if (menu_width < mbw->core.width) {
      menu_width = mbw->core.width - 2 * menu->core.border_width;
  }
     * */
  button_height = w->core.height + 2 * w->core.border_width;
  menu_height = menu->core.height + 2 * menu->core.border_width;

  XtTranslateCoords(w, 0, 0, &button_x, &button_y);
  menu_x = button_x;
  menu_y = button_y + button_height;

  if (menu_x >= 0) {
    int scr_width = WidthOfScreen(XtScreen(menu));
    if (menu_x + menu_width > scr_width)
      menu_x = scr_width - menu_width;
  }
  if (menu_x < 0) 
    menu_x = 0;

  if (menu_y >= 0) {
    int scr_height = HeightOfScreen(XtScreen(menu));
    if (menu_y + menu_height > scr_height)
      menu_y = scr_height - menu_height;
  }
  if (menu_y < 0)
    menu_y = 0;

  num_args = 0;
  XtSetArg(arglist[num_args], XtNx, menu_x); num_args++;
  XtSetArg(arglist[num_args], XtNy, menu_y); num_args++;
  XtSetValues(menu, arglist, num_args);

  XtPopupSpringLoaded(menu);
}

