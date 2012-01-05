/*
 * vector
 * 
 *   vector draw callback handlers
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
#include "jsui.h"
#include "log.h"
#include "tool_cb.h"
#include "tools.h"
#include "brushes.h"
#include "cursors.h"
#include "dialogs.h"


////////////////////////////////////////////////////////////////////////////////
// line

void
tools_vector_handler (
        int mouse_event,
        int mouse_buttons,
	int keyhit,
        int x,
        int y
)
{
    static int startx;
    static int starty;
    int real_mode = drawing_mode;

    switch (mouse_event)
    {
        case (TOOL_EVENT_INIT):
	    CURSOR_CROSSHAIRS();
            LOG_DEBUG("vector");
            startx = x;
            starty = y;
            jsui_dialog_tell_message( toolbar_dialog, 
                        TOOLBAR_VECTOR, JSUI_MSG_TRIGGER_L );
            break;

	case (TOOL_EVENT_DEINIT):
	    Page_Negative(page_rubberband);
	    break;

        case (TOOL_EVENT_STARTDOWN):
	    Page_Negative(page_rubberband);
	    Page_Undo_Checkpoint(page_active);
            startx = x;
            starty = y;
            break;

        case (TOOL_EVENT_DRAGGING):
	case (TOOL_EVENT_DRAG_STAT):
	    Page_Negative(page_rubberband);
	    if (mouse_buttons == 1)
		primitive_line(page_rubberband, pen_cycle,
				primitive_pixel,
				startx, starty, x, y);

	    else if (mouse_buttons == 3)
	    {
		drawing_mode = DRAW_STYLE_BGCOLOR;
		primitive_line(page_rubberband, pen_cycle,
				primitive_pixel,
				startx, starty, x, y);
	    }
            break;

        case (TOOL_EVENT_RELEASE):
	    Page_Negative(page_rubberband);
	    if (mouse_buttons == 1)
		primitive_line(page_active, page_active->fgpen, 
				(brush_active)?prim_brush:primitive_pixel,
				startx, starty, x, y);

	    else if (mouse_buttons == 3)
	    {
		drawing_mode = DRAW_STYLE_BGCOLOR;
		primitive_line(page_active, page_active->bgpen, 
				(brush_active)?prim_brush:primitive_pixel,
				startx, starty, x, y);
	    }

            break;

        case (TOOL_EVENT_IDLE):
	    Page_Negative(page_rubberband);
	    if (brush_active)
		prim_brush(page_rubberband, page_active->fgpen, x, y);
	    else
		primitive_pixel(page_rubberband, page_active->fgpen, x, y);
	    break;

        case (TOOL_EVENT_NONE):
        default:
            break;

    }
    drawing_mode = real_mode;
}
