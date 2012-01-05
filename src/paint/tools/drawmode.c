#define _SYS_WAIT_H
/*
 * drawmode
 * 
 *   drawmode callback handlers
 */

/*
 * 4p - Pixel Pushing Paint Program
 * Copyright (C) 2000 Scott "Jerry" Lawrence
 *                    jsl.4p@absynth.com
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
#include "SDL.h"
#include "jsui.h"
#include "log.h"
#include "tool_cb.h"
#include "tools.h"
#include "strings.h"

////////////////////////////////////////////////////////////////////////////////
// drawing modes

char * drawmode_text = STR_LK( STRINGS_COLOR );

void
tools_mode_change (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	switch (keyhit)
	{
	    case( SDLK_F1 ):
	    case( '!' ):
		LOG_DEBUG ("mode: Matte");
		drawing_mode = DRAW_STYLE_MATTE;
		drawmode_text = STR_LK( STRINGS_MATTE );
		/* force a menu redraw as well */
		break;

	    case( SDLK_F2 ):
	    case( '@' ):
		LOG_DEBUG ("mode: Color");
		drawing_mode = DRAW_STYLE_COLOR;
		drawmode_text = STR_LK( STRINGS_COLOR );
		/* force a menu redraw as well */
		break;

	    case( SDLK_F3 ):
	    case( '#' ):
		LOG_DEBUG ("mode: Replace");
		drawing_mode = DRAW_STYLE_REPLACE;
		drawmode_text = STR_LK( STRINGS_REPLACE );
		/* force a menu redraw as well */
		break;
	}
    }
}
