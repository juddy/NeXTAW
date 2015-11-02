/* 
 * Misc. functions for neXtaw 
 * 
 * Copyright (c) 1996 Alfedo K. Kojima
 */

#ifndef _MISC_H_
#define _MISC_H_

#include <X11/IntrinsicP.h>
#include <X11/neXtaw/ThreeDP.h>

#ifdef XPM_TILE

#ifndef XtNbackgroundTile
#define XtNbackgroundTile "backgroundTile"
#endif

#ifndef XtCBackgroundTile
#define XtCBackgroundTile "BackgroundTile"
#endif

#ifndef XtRTilePixmap
#define XtRTilePixmap	"BackgroundTile"
#endif

#endif

extern void
neXtawDrawShadowBox (Widget, ThreeDWidget, Position, Position, Position, 
		     Position, Boolean);

extern Boolean
neXtawcvtStringToTilePixmap ();

#endif
