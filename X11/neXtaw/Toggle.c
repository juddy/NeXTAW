/* $XConsortium: Toggle.c,v 1.28 94/04/17 20:13:17 kaleb Exp $ */
/* MODIFIED FOR N*XTSTEP LOOK	 				*/
/* Modifications Copyright (c) 1996,1997 by Alfredo Kojima	*/

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

 */

/*
 * Toggle.c - Toggle button widget
 *
 * Author: Chris D. Peterson
 *         MIT X Consortium 
 *         kit@expo.lcs.mit.edu
 *  
 * Date:   January 12, 1989
 *
 */

#include <stdio.h>

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include "XawInit.h"
#include <X11/Xmu/Converters.h>
#include <X11/Xmu/Misc.h>
#include "ToggleP.h"
#include "TraversalP.h"
#ifdef HAS_XMU_H
#include <X11/Xmu/Xmu.h>
#endif

/****************************************************************
 *
 * Full class record constant
 *
 ****************************************************************/

/* Private Data */

/* 
 * The order of toggle and notify are important, as the state has
 * to be set when we call the notify proc.
 */

static char defaultTranslations[] =
    "<EnterWindow>:	    FocusEnterWindow()	\n\
     <FocusIn>:		    highlight(Always)	\n\
     <LeaveWindow>:	    FocusLeaveWindow()	\n\
     <FocusOut>:	    unhighlight()	\n\
     <Btn1Down>,<Btn1Up>:   toggle() notify()	\n\
     Shift<Key>Tab:	    FocusPrevious()	\n\
     <Key>Tab:		    FocusNext()		\n\
     <Key>Home:		    FocusHome()		\n\
     <Key>End:		    FocusEnd()		\n\
     <Key>Up:		    FocusPreviousGroup()	\n\
     <Key>Down:		    FocusNextGroup()	\n\
     <Key>KP_Home:	    FocusHome()		\n\
     <Key>KP_End:	    FocusEnd()		\n\
     <Key>KP_Up:	    FocusPreviousGroup()	\n\
     <Key>KP_Down:	    FocusNextGroup()	\n\
     <KeyDown>space,<KeyUp>space:	toggle() notify()";

#define offset(field) XtOffsetOf(ToggleRec, field)

static XtResource resources[] = { 
   {XtNstate, XtCState, XtRBoolean, sizeof(Boolean), 
      offset(command.set), XtRString, "off"},
   {XtNradioGroup, XtCWidget, XtRWidget, sizeof(Widget), 
      offset(toggle.widget), XtRWidget, (XtPointer) NULL },
   {XtNradioData, XtCRadioData, XtRPointer, sizeof(XtPointer), 
      offset(toggle.radio_data), XtRPointer, (XtPointer) NULL },
   {XtNtoggleStyle, XtCToggleStyle, XtRToggleStyle, sizeof(XtToggleStyle),
      offset(toggle.toggle_style), XtRToggleStyle, (XtPointer)XtToggleSimple },
};

#undef offset


static void Toggle(), Initialize(), Notify(), ToggleSet();
static void ToggleHighlight(), ToggleUnhighlight();
static void ToggleDestroy(), ClassInit();
static Boolean SetValues();
static void Redisplay(), Resize();
static void DisplayCheckBox(Widget), DisplayRadioButton(Widget);

/* Functions for handling the Radio Group. */

static RadioGroup * GetRadioGroup();
static void CreateRadioGroup(), AddToRadioGroup(), TurnOffRadioSiblings();
static void RemoveFromRadioGroup();

static XtActionsRec actionsList[] =
{
  {"toggle",	        Toggle},
  {"notify",	        Notify},
  {"set",	        ToggleSet},
  /* the next three are from XawM */
#if 0
  {"unset",		ToggleUnset},
#endif
  {"highlight",		ToggleHighlight},
  {"unhighlight",	ToggleUnhighlight},
};


#define CHECKBOX_SPACE 12

#define SuperClass ((CommandWidgetClass)&commandClassRec)

ToggleClassRec toggleClassRec = {
  {
    (WidgetClass) SuperClass,		/* superclass		  */	
    "Toggle",				/* class_name		  */
    sizeof(ToggleRec),			/* size			  */
    ClassInit,				/* class_initialize	  */
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
    NULL,         			/* destroy		  */
    Resize,				/* resize		  */
    Redisplay,				/* expose		  */
    SetValues,				/* set_values		  */
    NULL,				/* set_values_hook	  */
    XtInheritSetValuesAlmost,		/* set_values_almost	  */
    NULL,				/* get_values_hook	  */
    XtInheritAcceptFocus,		/* accept_focus		  */
    XtVersion,				/* version		  */
    NULL,				/* callback_private	  */
    defaultTranslations,		/* tm_table		  */
    XtInheritQueryGeometry,		/* query_geometry	  */
    XtInheritDisplayAccelerator,	/* display_accelerator	  */
    NULL				/* extension		  */
  },  /* CoreClass fields initialization */
  {
    XtInheritChangeSensitive		/* change_sensitive	  */ 
  },  /* SimpleClass fields initialization */
  {
    XtInheritXaw3dShadowDraw            /* shadowdraw          */
  },  /* ThreeDClass fields initialization */
  {
    0                                     /* field not used    */
  },  /* LabelClass fields initialization */
  {
    0                                     /* field not used    */
  },  /* CommandClass fields initialization */
  {
      NULL,			        /* Set Procedure. */
      NULL,			        /* Unset Procedure. */
      NULL			        /* extension. */
  }  /* ToggleClass fields initialization */
};

  /* for public consumption */
WidgetClass toggleWidgetClass = (WidgetClass) &toggleClassRec;

/****************************************************************
 *
 * Private Procedures
 *
 ****************************************************************/
#define	done(address, type) \
	{ toVal->size = sizeof(type); \
	  toVal->addr = (XPointer) address; \
	  return; \
	}


static XrmQuark	XtQToggleSimple, XtQToggleCheck, XtQToggleRadio;

/* ARGSUSED */
static void _CvtStringToToggleStyle(XrmValuePtr args, Cardinal *num_args,
	XrmValuePtr fromVal, XrmValuePtr toVal)
{
    static XtToggleStyle toggleStyle;
    XrmQuark q;
    char lowerName[1000];

    XmuCopyISOLatin1Lowered (lowerName, (char*)fromVal->addr);
    q = XrmStringToQuark(lowerName);
    if (q == XtQToggleSimple) {
	toggleStyle = XtToggleSimple;
	done(&toggleStyle, XtToggleStyle);
    }
    if (q == XtQToggleCheck) {
	toggleStyle = XtToggleCheck;
	done(&toggleStyle, XtToggleStyle);
    }
    if (q == XtQToggleRadio) {
	toggleStyle = XtToggleRadio;
	done(&toggleStyle, XtToggleStyle);
    }
    XtStringConversionWarning(fromVal->addr, "toggleStyle");
    toVal->addr = NULL;
    toVal->size = 0;
}
#undef done

static void
ClassInit(void)
{
  XtActionList actions;
  Cardinal num_actions;
  Cardinal i;
  ToggleWidgetClass class = (ToggleWidgetClass) toggleWidgetClass;
  static XtConvertArgRec parentCvtArgs[] = {
      {XtBaseOffset, (XtPointer)XtOffsetOf(WidgetRec, core.parent),
	   sizeof(Widget)}
  };

  XawInitializeWidgetSet();
  XtSetTypeConverter(XtRString, XtRWidget, XmuNewCvtStringToWidget,
		     parentCvtArgs, XtNumber(parentCvtArgs), XtCacheNone,
		     (XtDestructor)NULL);
    
  XtQToggleSimple  = XrmPermStringToQuark("simple");
  XtQToggleCheck = XrmPermStringToQuark("check");
  XtQToggleRadio = XrmPermStringToQuark("radio");
  XtAddConverter( XtRString, XtRToggleStyle, _CvtStringToToggleStyle, 
		 (XtConvertArgList)NULL, 0 );
/* 
 * Find the set and unset actions in the command widget's action table. 
 */

  XtGetActionList(commandWidgetClass, &actions, &num_actions);

  for (i = 0 ; i < num_actions ; i++) {
    if (streq(actions[i].string, "set"))
	class->toggle_class.Set = actions[i].proc;
    if (streq(actions[i].string, "unset")) 
	class->toggle_class.Unset = actions[i].proc;

    if ( (class->toggle_class.Set != NULL) &&
	 (class->toggle_class.Unset != NULL) ) {
	XtFree((char *) actions);
	return;
    }
  }  

/* We should never get here. */
  XtError("Aborting, due to errors resolving bindings in the Toggle widget.");
}

/*ARGSUSED*/
static void Initialize(Widget request, Widget new,
	ArgList *args, Cardinal *num_args)
{
    ToggleWidget tw = (ToggleWidget) new;
    ToggleWidget tw_req = (ToggleWidget) request;

    tw->toggle.radio_group = NULL;
    
    if (tw->toggle.radio_data == NULL) 
      tw->toggle.radio_data = (XtPointer) new->core.name;

    if (tw->toggle.widget != NULL) {
      if ( GetRadioGroup(tw->toggle.widget) == NULL) 
	CreateRadioGroup(new, tw->toggle.widget);
      else
	AddToRadioGroup( GetRadioGroup(tw->toggle.widget), new);
    }      
    XtAddCallback(new, XtNdestroyCallback, ToggleDestroy, (XtPointer)NULL);

/*
 * Command widget assumes that the widget is unset, so we only 
 * have to handle the case where it needs to be set.
 *
 * If this widget is in a radio group then it may cause another
 * widget to be unset, thus calling the notify proceedure.
 *
 * I want to set the toggle if the user set the state to "On" in 
 * the resource group, reguardless of what my ancestors did.
 */

    if (tw_req->command.set) 
      ToggleSet(new, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);

    if (tw->toggle.toggle_style==XtToggleCheck
	|| tw->toggle.toggle_style==XtToggleRadio) {
	/* if we'll use an indicator */
	tw->threeD.shadow_width = 0;
	XtResizeWidget(new, tw->core.width + CHECKBOX_SPACE, tw->core.height,
		       tw->core.border_width);
    }
}

static void
DisplayRadioButton(Widget w/*, Boolean toggled*/)
{
    ToggleWidget tw = (ToggleWidget) w;
    Display *dpy=XtDisplay(w);
    Window win=XtWindow(w);
    GC light2 = tw->threeD.top_shadow_GC;
    GC light = tw->threeD.top_half_shadow_GC;
    GC dark2 = tw->threeD.bot_shadow_GC;      
    GC dark = tw->threeD.bot_half_shadow_GC;
    Dimension	s = tw->threeD.shadow_width;    
    int x1, y1;

    if (!XtIsRealized(w)) return;
    x1 = s+1;
    y1 = (tw->core.height-15)/2;
    if (y1<0) 
      y1=0;

    /*
     * These coords are based on trial and error
     */
#define rad 7
    XDrawArc(dpy, win, dark, x1, y1, rad*2-1, rad*2-1, 60*64, 150*64);
    XDrawArc(dpy, win, dark2, x1, y1, rad*2, rad*2, 55*64, 160*64);
    XDrawArc(dpy, win, light, x1, y1, rad*2, rad*2, 35*64, -160*64);
    XDrawArc(dpy, win, dark, x1+1, y1+1, rad*2-1, rad*2-1, 60*64, 150*64);
    XDrawArc(dpy, win, light2, x1, y1, rad*2-1, rad*2-1, 30*64, -150*64);
    if (tw->command.set) {
	XFillArc(dpy, win, light, x1+3, y1+3, (rad-2)*2, (rad-2)*2, 0, 360*64);
    }
#undef rad
}


static void
DisplayCheckBox(Widget w)
{
    ToggleWidget tw = (ToggleWidget) w;
    Display *dpy=XtDisplay(w);
    Window win=XtWindow(w);
    GC light2 = tw->threeD.top_shadow_GC;
    GC light = tw->threeD.top_half_shadow_GC;
    GC dark2 = tw->threeD.bot_shadow_GC;      
    GC dark = tw->threeD.bot_half_shadow_GC;
    Dimension	s = tw->threeD.shadow_width;    
    int x1, y1, x2, y2;

    if (!XtIsRealized(w)) return;    
    x1 = s+1;
    x2 = s+15;
    if (x2>tw->core.width) {
	x2=tw->core.width-x1;
    }
    y1 = (tw->core.height-15)/2;
    y2 = y1+15;
    if (y1<0) {
	y1=0;
	y2=tw->core.height;
    }
    XDrawLine(dpy, win, light, x1, y1, x2, y1);
    XDrawLine(dpy, win, light, x1, y1, x1, y2);
    XDrawLine(dpy, win, dark, x1, y2, x2, y2);
    XDrawLine(dpy, win, dark, x2, y1, x2, y2);
    
    XDrawLine(dpy, win, light2, x1+1, y1+1, x2-1, y1+1);
    XDrawLine(dpy, win, light2, x1+1, y1+1, x1+1, y2-1); 
    XDrawLine(dpy, win, dark2, x1+1, y2-1, x2-1, y2-1);
    XDrawLine(dpy, win, dark2, x2-1, y1+1, x2-1, y2-1);    
    if (tw->command.set) {
#if 0	/* this can't work */
	int y=(y2-y1)/2-s;
#else	/* this can */
#define y (y1+3)
#endif
#define x (x1+4)
	XDrawLine(dpy, win, dark2, x+1, y+3, x+1, y+6);
	XDrawLine(dpy, win, light, x, y+3, x, y+8);     
	XDrawLine(dpy, win, light, x, y+8, x+8, y);
	XDrawLine(dpy, win, dark2, x, y+9, x+8, y+1);
	XDrawLine(dpy, win, dark, x+1, y+9, x+8, y+2);
#undef x
    }    
}

static void
Resize(Widget w)
{
    ToggleWidget tw = (ToggleWidget) w;
    int tmp = 0;
    Pixmap kludge = None;

    /* AAAARGHHH!! */
    if (tw->toggle.toggle_style==XtToggleCheck
	|| tw->toggle.toggle_style==XtToggleRadio) {
	tmp = tw->label.lbm_width;
	kludge = tw->label.left_bitmap;
	tw->label.lbm_width += CHECKBOX_SPACE;
	tw->label.left_bitmap = 1;
    }    
    (*SuperClass->core_class.resize) (w);
    if (tw->toggle.toggle_style==XtToggleCheck
	|| tw->toggle.toggle_style==XtToggleRadio) {
	tw->label.lbm_width = tmp;
	tw->label.left_bitmap = kludge;
    }    
}

static void
Redisplay(Widget w, XEvent *event, Region region)
{
    ToggleWidget tw = (ToggleWidget) w;

    (*SuperClass->core_class.expose) (w, event, region);
    if (tw->toggle.toggle_style==XtToggleCheck) {
	DisplayCheckBox(w);
    } else if (tw->toggle.toggle_style==XtToggleRadio) {
	DisplayRadioButton(w);
    }
}



/************************************************************
 *
 *  Action Procedures
 *
 ************************************************************/

/* ARGSUSED */
static void 
ToggleSet(Widget w,XEvent *event,String *params,Cardinal *num_params)
{
    ToggleWidgetClass class = (ToggleWidgetClass) w->core.widget_class;

    TurnOffRadioSiblings(w);
    class->toggle_class.Set(w, event, NULL, 0);
    if (((ToggleWidget)w)->toggle.toggle_style==XtToggleCheck) {
	DisplayCheckBox(w);
    } else if (((ToggleWidget)w)->toggle.toggle_style==XtToggleRadio) {
    	DisplayRadioButton(w);
    }    
}

static void
ToggleHighlight(Widget w, XEvent *event,
		String *params, Cardinal *num_params)
{
    ToggleWidget tw = (ToggleWidget)w;
  if ( *num_params == (Cardinal) 0) 
    tw->command.highlighted = HighlightWhenUnset;
  else {
    if ( *num_params != (Cardinal) 1) 
      XtWarning("Too many parameters passed to highlight action table.");
    switch (params[0][0]) {
    case 'A':
    case 'a':
      tw->command.highlighted = HighlightAlways;
      break;
    default:
      tw->command.highlighted = HighlightWhenUnset;
      break;
    }
  }

#if 0
    if (((ToggleWidget)w)->toggle.toggle_style==XtToggleCheck) {
	DisplayCheckBox(w);
    } else if (((ToggleWidget)w)->toggle.toggle_style==XtToggleRadio) {
    	DisplayRadioButton(w);
    }    
#else
	Redisplay(w, event, NULL);
#endif
}

static void
ToggleUnhighlight(Widget w, XEvent *event,
		String *params, Cardinal *num_params)
{
    ToggleWidget tw = (ToggleWidget)w;
    tw->command.highlighted = HighlightNone;
#if 0
    if (((ToggleWidget)w)->toggle.toggle_style==XtToggleCheck) {
	DisplayCheckBox(w);
    } else if (((ToggleWidget)w)->toggle.toggle_style==XtToggleRadio) {
    	DisplayRadioButton(w);
    }    
#else
	Redisplay(w, event, NULL);
#endif
}

/* ARGSUSED */
static void 
Toggle(Widget w,XEvent *event,String *params,Cardinal *num_params)
{
  ToggleWidget tw = (ToggleWidget)w;
  ToggleWidgetClass class = (ToggleWidgetClass) w->core.widget_class;

  if (tw->command.set) {
      class->toggle_class.Unset(w, event, NULL, 0);
      if (tw->toggle.toggle_style==XtToggleCheck) {
	  DisplayCheckBox(w);
      } else if (tw->toggle.toggle_style==XtToggleRadio) {
	  DisplayRadioButton(w);
      }      
  } else {
      ToggleSet(w, event, params, num_params);
  }    
    
}

/* ARGSUSED */
static void Notify(Widget w,XEvent *event,String params,Cardinal *num_params)
{
  ToggleWidget tw = (ToggleWidget) w;
  long antilint = tw->command.set;

  XtCallCallbacks( w, XtNcallback, (XtPointer) antilint );
}

/************************************************************
 *
 * Set specified arguments into widget
 *
 ***********************************************************/

/* ARGSUSED */
static Boolean 
SetValues (Widget current, Widget request, Widget new,
	ArgList args, Cardinal *num_args)
{
    ToggleWidget oldtw = (ToggleWidget) current;
    ToggleWidget tw = (ToggleWidget) new;
    ToggleWidget rtw = (ToggleWidget) request;

    if (oldtw->toggle.widget != tw->toggle.widget)
      XawToggleChangeRadioGroup(new, tw->toggle.widget);

    if (!tw->core.sensitive && oldtw->core.sensitive && rtw->command.set)
	tw->command.set = True;

    if (oldtw->command.set != tw->command.set) {
	tw->command.set = oldtw->command.set;
	Toggle(new, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);
    }
    return(FALSE);
}

/*	Function Name: ToggleDestroy
 *	Description: Destroy Callback for toggle widget.
 *	Arguments: w - the toggle widget that is being destroyed.
 *                 junk, grabage - not used.
 *	Returns: none.
 */

/* ARGSUSED */
static void
ToggleDestroy(Widget w, XtPointer junk, XtPointer garbage)
{
  RemoveFromRadioGroup(w);
}

/************************************************************
 *
 * Below are all the private procedures that handle 
 * radio toggle buttons.
 *
 ************************************************************/

/*	Function Name: GetRadioGroup
 *	Description: Gets the radio group associated with a give toggle
 *                   widget.
 *	Arguments: w - the toggle widget who's radio group we are getting.
 *	Returns: the radio group associated with this toggle group.
 */

static RadioGroup *
GetRadioGroup(Widget w)
{
  ToggleWidget tw = (ToggleWidget) w;

  if (tw == NULL) return(NULL);
  return( tw->toggle.radio_group );
}

/*	Function Name: CreateRadioGroup
 *	Description: Creates a radio group. give two widgets.
 *	Arguments: w1, w2 - the toggle widgets to add to the radio group.
 *	Returns: none.
 * 
 *      NOTE:  A pointer to the group is added to each widget's radio_group
 *             field.
 */

static void
CreateRadioGroup(Widget w1, Widget w2)
{
  char error_buf[BUFSIZ];
  ToggleWidget tw1 = (ToggleWidget) w1;
  ToggleWidget tw2 = (ToggleWidget) w2;

  if ( (tw1->toggle.radio_group != NULL) || (tw2->toggle.radio_group != NULL) ) {
    (void) sprintf(error_buf, "%s %s", "Toggle Widget Error - Attempting",
	    "to create a new toggle group, when one already exists.");
    XtWarning(error_buf);
  }
  AddToRadioGroup( (RadioGroup *)NULL, w1 );
  AddToRadioGroup( GetRadioGroup(w1), w2 );
}

/*	Function Name: AddToRadioGroup
 *	Description: Adds a toggle to the radio group.
 *	Arguments: group - any element of the radio group the we are adding to.
 *                 w - the new toggle widget to add to the group.
 *	Returns: none.
 */

static void
AddToRadioGroup(RadioGroup *group, Widget w)
{
  ToggleWidget tw = (ToggleWidget) w;
  RadioGroup * local;

  local = (RadioGroup *) XtMalloc( sizeof(RadioGroup) );
  local->widget = w;
  tw->toggle.radio_group = local;
  if (group == NULL) {		/* Creating new group. */
    group = local;
    group->next = NULL;
    group->prev = NULL;
    return;
  }
  local->prev = group;		/* Adding to previous group. */
  if ((local->next = group->next) != NULL)
      local->next->prev = local;
  group->next = local;
}

/*	Function Name: TurnOffRadioSiblings
 *	Description: Deactivates all radio siblings.
 *	Arguments: widget - a toggle widget.
 *	Returns: none.
 */

static void
TurnOffRadioSiblings(Widget w)
{
  RadioGroup * group;
  ToggleWidgetClass class = (ToggleWidgetClass) w->core.widget_class;

  if ( (group = GetRadioGroup(w)) == NULL)  /* Punt if there is no group */
    return;

  /* Go to the top of the group. */

  for ( ; group->prev != NULL ; group = group->prev );

  while ( group != NULL ) {
    ToggleWidget local_tog = (ToggleWidget) group->widget;
    if ( local_tog->command.set ) {
      class->toggle_class.Unset(group->widget, NULL, NULL, 0);
	
      if (local_tog->toggle.toggle_style==XtToggleCheck) {
	    DisplayCheckBox((Widget)local_tog);
      } else if (local_tog->toggle.toggle_style==XtToggleRadio) {
	    DisplayRadioButton((Widget)local_tog);
      }
	
      Notify( group->widget, (XEvent *)NULL, (String)NULL, (Cardinal *)0);
    }
    group = group->next;
  }
}

/*	Function Name: RemoveFromRadioGroup
 *	Description: Removes a toggle from a RadioGroup.
 *	Arguments: w - the toggle widget to remove.
 *	Returns: none.
 */

static void
RemoveFromRadioGroup(Widget w)
{
  RadioGroup * group = GetRadioGroup(w);
  if (group != NULL) {
    if (group->prev != NULL)
      (group->prev)->next = group->next;
    if (group->next != NULL)
      (group->next)->prev = group->prev;
    XtFree((char *) group);
  }
}

/************************************************************
 *
 * Public Routines
 *
 ************************************************************/
   
/*	Function Name: XawToggleChangeRadioGroup
 *	Description: Allows a toggle widget to change radio groups.
 *	Arguments: w - The toggle widget to change groups.
 *                 radio_group - any widget in the new group.
 *	Returns: none.
 */

void
XawToggleChangeRadioGroup(Widget w, Widget radio_group)
{
  ToggleWidget tw = (ToggleWidget) w;
  RadioGroup * group;

  RemoveFromRadioGroup(w);

/*
 * If the toggle that we are about to add is set then we will 
 * unset all toggles in the new radio group.
 */

  if ( tw->command.set && radio_group != NULL )
    XawToggleUnsetCurrent(radio_group);

  if (radio_group != NULL) {
      if ((group = GetRadioGroup(radio_group)) == NULL)
	  CreateRadioGroup(w, radio_group);
      else AddToRadioGroup(group, w);
  }
}

/*	Function Name: XawToggleGetCurrent
 *	Description: Returns the RadioData associated with the toggle
 *                   widget that is currently active in a toggle group.
 *	Arguments: w - any toggle widget in the toggle group.
 *	Returns: The XtNradioData associated with the toggle widget.
 */

XtPointer
XawToggleGetCurrent(Widget w)
{
  RadioGroup * group;

  if ( (group = GetRadioGroup(w)) == NULL) return(NULL);
  for ( ; group->prev != NULL ; group = group->prev);

  while ( group != NULL ) {
    ToggleWidget local_tog = (ToggleWidget) group->widget;
    if ( local_tog->command.set )
      return( local_tog->toggle.radio_data );
    group = group->next;
  }
  return(NULL);
}

/*	Function Name: XawToggleSetCurrent
 *	Description: Sets the Toggle widget associated with the
 *                   radio_data specified.
 *	Arguments: radio_group - any toggle widget in the toggle group.
 *                 radio_data - radio data of the toggle widget to set.
 *	Returns: none.
 */

void
XawToggleSetCurrent(Widget radio_group, XtPointer radio_data)
{
  RadioGroup * group;
  ToggleWidget local_tog; 

/* Special case of no radio group. */

  if ( (group = GetRadioGroup(radio_group)) == NULL) {
    local_tog = (ToggleWidget) radio_group;
    if ( (local_tog->toggle.radio_data == radio_data) )     
      if (!local_tog->command.set) {
	ToggleSet((Widget) local_tog, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);
	Notify((Widget) local_tog, (XEvent *)NULL, (String)NULL, (Cardinal *)0);
      }
    return;
  }

/*
 * find top of radio_roup 
 */

  for ( ; group->prev != NULL ; group = group->prev);

/*
 * search for matching radio data.
 */

  while ( group != NULL ) {
    local_tog = (ToggleWidget) group->widget;
    if ( (local_tog->toggle.radio_data == radio_data) ) {
      if (!local_tog->command.set) { /* if not already set. */
	ToggleSet((Widget) local_tog, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);
	Notify((Widget) local_tog, (XEvent *)NULL, (String)NULL, (Cardinal *)0);
      }
      return;			/* found it, done */
    }
    group = group->next;
  }
}
 
/*	Function Name: XawToggleUnsetCurrent
 *	Description: Unsets all Toggles in the radio_group specified.
 *	Arguments: radio_group - any toggle widget in the toggle group.
 *	Returns: none.
 */

void
XawToggleUnsetCurrent(Widget radio_group)
{
  ToggleWidgetClass class;
  ToggleWidget local_tog = (ToggleWidget) radio_group;

  /* Special Case no radio group. */

  if (local_tog->command.set) {
    class = (ToggleWidgetClass) local_tog->core.widget_class;
    class->toggle_class.Unset(radio_group, NULL, NULL, 0);
    Notify(radio_group, (XEvent *)NULL, (String)NULL, (Cardinal *)0);
  }
  if ( GetRadioGroup(radio_group) == NULL) return;
  TurnOffRadioSiblings(radio_group);
}

