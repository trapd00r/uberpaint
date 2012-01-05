/*
** Manager
*/

/*
 * 4p - Pixel Pushing Paint Program
 * Copyright (C) 2008 Scott "Jerry" Lawrence
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

#include <stdio.h>
#include "jsui.h"
#include "strings.h"
#include "version.h"
#include "paint.h"
#include "prefs.h"

int manager_cb(JSUI_DIALOG * d, int object, int msg)
{
    if (!d) return( JSUI_R_O_K );

    if(msg != JSUI_MSG_LRELEASE) return( JSUI_R_O_K );

    switch(object)
    {
    case( 1 ):
	jsui_dialog_broadcast( PAINT_MSG_MENUPOP, MENUPOP_MAIN );
	break;
    }
    return JSUI_R_O_K;
}

char zoombuf[32] = "Zoom: 100%";

JSUI_DIALOG manager_dialog[] =
{
   /* (dialog proc)     (x)   (y)   (w)   (h)   
		(key) (flags)  (d1)  (d2)  (dp) (dp2) (dp3) */

    {jsui_widget_frame, 0, 0, 150, 60, 0, 
            JSUI_FRAME_DRAGGABLE | JSUI_FRAME_TITLEBAR,
	    0,
            0, STRINGS_4P " " J_VERSION, NULL, NULL  },

    /* 1 */
    {jsui_widget_button,  2, 2, 146, 18, 0, 0, 
		0, 0, 
		STR_LK( STRINGS_MENU ), NULL, (void *)manager_cb},

	/* 2 */
    {jsui_widget_text, 2, 30, 146, 0, 0,
		JSUI_F_NOFRAME, JSUI_T_CENTER, 0, 
		zoombuf, NULL, NULL},

    {jsui_widget_text, 2, 50, 146, 0, 0,
		JSUI_F_NOFRAME, JSUI_T_CENTER, 0, 
		"Ready " J_REVISION, NULL, NULL},

    JSUI_DLG_END
};

void manager_status( char * text )
{
	manager_dialog[3].dp = text;
	jsui_dialog_send_message( manager_dialog, JSUI_MSG_DRAW, 0 );
}

void manager_zoom( int percent )
{
	if( percent > 16000 ) percent = 16000;
	if( percent < 0 ) percent = 0;
	snprintf( zoombuf, 32, "Zoom: %d%%", percent );
	jsui_dialog_send_message( manager_dialog, JSUI_MSG_DRAW, 0 );
}
