/*
** dialogs.h
**
*/

/*
 * 4p - Pixel Pushing Paint Program
 * Copyright (C) 2000 Scott "Jerry" Lawrence
 *                    jsl.4p@umlautllama.com
 *
 *  This is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "jsui.h"

extern JSUI_DIALOG manager_dialog[];
extern JSUI_DIALOG menus_dialog[];
extern JSUI_DIALOG brushes_dialog[];
extern JSUI_DIALOG toolbar_dialog[];
extern JSUI_DIALOG colors_dialog[];
extern JSUI_DIALOG palette_edit_dialog[];

/* here's the status setting function for the manager dialog */
void manager_status( char * text );

/* and here's where you set the display of the zoom level */
void manager_zoom( int percent );


/* these need to be the indexes in the toolbar struct */
/* these are to tell the toolbar to 'press' when a key shortcut is used */
#define TOOLBAR_DOTTED          (1)
#define TOOLBAR_CONTINUOUS      (2)
#define TOOLBAR_VECTOR          (3)
#define TOOLBAR_CURVE           (4)
#define TOOLBAR_FLOOD           (5)
#define TOOLBAR_AIRBRUSH        (6)
#define TOOLBAR_RECTANGLE       (7)
#define TOOLBAR_CIRCLE          (8)
#define TOOLBAR_OVAL            (9)
#define TOOLBAR_POLYLINE        (10)
#define TOOLBAR_SNAGBRUSH       (11)
#define TOOLBAR_TEXT            (12)
#define TOOLBAR_GRID            (13)
#define TOOLBAR_MIRROR          (14)
#define TOOLBAR_MAGNIFY         (15)
#define TOOLBAR_ZOOMIN          (16)
#define TOOLBAR_UNDO            (17)
#define TOOLBAR_CLEAR           (18)

