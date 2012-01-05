/*
 * brush
 * 
 *   brush tools callback handlers
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
#include "tool_cb.h"
#include "tools.h"
#include "brushes.h"
#include "cursors.h"
#include "dialogs.h"
#include "log.h"



////////////////////////////////////////////////////////////////////////////////
// snag brush


void
tools_snag_brush_handler (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    static int startx;
    static int starty;

    switch (mouse_event)
    {
	case (TOOL_EVENT_INIT):
	    CURSOR_CROSSHAIRS();
	    Page_Negative(page_rubberband);
	    LOG_DEBUG("brush");
	    startx = x;
	    starty = y;
            jsui_dialog_tell_message( toolbar_dialog, 
                        TOOLBAR_SNAGBRUSH, JSUI_MSG_TRIGGER_L );
	    break;

	case (TOOL_EVENT_DEINIT):
	    Page_Negative(page_rubberband);
	    break;

	case (TOOL_EVENT_STARTDOWN):
	    startx = x;
	    starty = y;
	    break;

	case (TOOL_EVENT_DRAGGING):
	case (TOOL_EVENT_DRAG_STAT):
	    Page_Negative(page_rubberband);
	    if (mouse_buttons == 1)
	    {
		primitive_rectangle_hollow(page_rubberband, pen_cycle,
			primitive_pixel, startx, starty, x, y);

	    }
	    else if (mouse_buttons == 3)
	    {
		primitive_rectangle_hollow(page_rubberband, pen_cycle,
			primitive_pixel, startx, starty, x, y);
	    }
	    break;

	case (TOOL_EVENT_RELEASE):
	    Page_Negative(page_rubberband);
/*
	    printf ("Snag brush:  (%d,%d) - (%d,%d)  %d %d\n", 
			x, y, startx, starty, 
			ABS(x-startx), ABS(y-starty));
*/
	    LOG_DEBUG( "snag brush" );

            if (brush_custom)  Page_Destroy(brush_custom);

	    brush_custom = Page_Cutout_Brush(
				page_active, startx, starty, x, y,
				excl_brush, 
				(mouse_buttons == 3)?page_active->bgpen:NULL);

	    brush_active = brush_custom;
				
	    jsui_dialog_broadcast(PAINT_MSG_DOTTEDDRAW, 0);
	    jsui_dialog_broadcast(PAINT_MSG_MODEMATTE, 0);
	    drawing_mode = DRAW_STYLE_MATTE;
	    break;


	case (TOOL_EVENT_IDLE):
	    Page_Negative(page_rubberband);
	    primitive_crosshairs(page_rubberband, x, y);
	    break;

	case (TOOL_EVENT_NONE):
	default:
	    break;

    }
}



void
tools_brush_circlesize (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG( "circle brush size" );

	if (brush_circle) Page_Destroy(brush_circle);
	brush_circle = NULL;
	
	brush_size   = keyhit;
	if (brush_size == 0)
	{
	    brush_active = NULL;
	} else {
	    brush_circle = brush_create_circle(brush_size);
	    brush_active = brush_circle;
	}
	drawing_mode = DRAW_STYLE_COLOR;
	jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
    }
}

void
tools_brush_squaresize (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG( "square brush size" );

	if (brush_square) Page_Destroy(brush_square);
	brush_square = NULL;

	brush_size = keyhit;
	if (brush_size == 0)
	{
	    brush_active = NULL;
	} else {
	    brush_square = brush_create_square(brush_size);
	    brush_active = brush_square;
	}
	drawing_mode = DRAW_STYLE_COLOR;
	jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
    }
}

void
tools_brush_increase (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	if (brush_active == NULL)
	{
	    brush_size = 0;
	    brush_active = brush_circle;
	}

	if (brush_active == brush_circle)
	{
	    brush_size++;
	    LOG_DEBUG( "increase circle" );

	    if (brush_circle) Page_Destroy(brush_circle);
	    brush_circle = brush_create_circle(brush_size);
	    brush_active = brush_circle;

	    jsui_dialog_broadcast(PAINT_MSG_CIRCLEBRUSHSIZE, brush_size);
	    drawing_mode = DRAW_STYLE_COLOR;
	    jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
	}
	else if (brush_active == brush_square)
	{
	    brush_size++;
	    LOG_DEBUG( "increase square" );

	    if (brush_square) Page_Destroy(brush_square);
	    brush_square = brush_create_square(brush_size);
	    brush_active = brush_square;

	    jsui_dialog_broadcast(PAINT_MSG_SQUAREBRUSHSIZE, brush_size);
	    drawing_mode = DRAW_STYLE_COLOR;
	    jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
	}
    }
}

void
tools_brush_decrease (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG( "decrease brush size" );

	if ( (brush_active == brush_circle) ||
	     (brush_active == brush_square) )
	{
	    if (brush_size == 1)
	    {
		brush_active = NULL;
		jsui_dialog_broadcast(PAINT_MSG_CIRCLEBRUSHSIZE, 0);
	    }

	    if (brush_size > 1)
	    {
		brush_size--;

		if (brush_active == brush_circle)
		{
		    LOG_DEBUG( "decreaase circle" );

		    if (brush_circle) Page_Destroy(brush_circle);
		    brush_circle = brush_create_circle(brush_size);
		    brush_active = brush_circle;
		    jsui_dialog_broadcast(PAINT_MSG_CIRCLEBRUSHSIZE, brush_size);
		}
		else if (brush_active == brush_square)
		{
		    LOG_DEBUG( "decreaase square" );

		    if (brush_square) Page_Destroy(brush_square);
		    brush_square = brush_create_square(brush_size);
		    brush_active = brush_square;
		    if ( brush_size == 1 )
		    {
			brush_active = NULL;
			jsui_dialog_broadcast(PAINT_MSG_CIRCLEBRUSHSIZE, 0);
		    } else 
			jsui_dialog_broadcast(PAINT_MSG_SQUAREBRUSHSIZE, brush_size);
		}
		drawing_mode = DRAW_STYLE_COLOR;
		jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
	    }
	}
    }
}

void
tools_dot (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG( "dot" );

	brush_size = 0;
	brush_active = NULL;
	drawing_mode = DRAW_STYLE_COLOR;

	jsui_dialog_broadcast(PAINT_MSG_CIRCLEBRUSHSIZE, 0);
	jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
    }
}


void
tools_retrieve_old_brush (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG( "old brush swap" );
	
	if (brush_custom)
	{
	    LOG_DEBUG( "switch to custom" );
	    brush_size   = 0;
	    brush_active = brush_custom;
	    drawing_mode = DRAW_STYLE_MATTE;
	    jsui_dialog_broadcast(PAINT_MSG_CIRCLEBRUSHSIZE, 0);
	    jsui_dialog_broadcast(PAINT_MSG_MODEMATTE, 0);
	}
    }
}



void
tools_brush_circle (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG( "switch to circle" );

	if (brush_circle) Page_Destroy(brush_circle);
	brush_circle = brush_create_circle(brush_size);
	brush_active = brush_circle;
	drawing_mode = DRAW_STYLE_COLOR;
	jsui_dialog_broadcast(PAINT_MSG_CIRCLEBRUSHSIZE, brush_size);
	jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
    }
}

void
tools_brush_square (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG("switch to square brush");

	if (brush_square) Page_Destroy(brush_square);
	brush_square = brush_create_square(brush_size);
	brush_active = brush_square;
	drawing_mode = DRAW_STYLE_COLOR;

	jsui_dialog_broadcast(PAINT_MSG_SQUAREBRUSHSIZE, brush_size);
	jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
    }
}


////////////////////////////////////////////////////////////////////////////////

void
tools_brush_3 (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG("scatterbrush 3");

	brush_active = brush_3;
	drawing_mode = DRAW_STYLE_COLOR;
	//jsui_dialog_broadcast(PAINT_MSG_BRUSH3, 0);
	jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
    }
}


void
tools_brush_5 (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG("scatterbrush 5");

	brush_active = brush_5;
	drawing_mode = DRAW_STYLE_COLOR;
	//jsui_dialog_broadcast(PAINT_MSG_BRUSH5, 0);
	jsui_dialog_broadcast(PAINT_MSG_MODECOLOR, 0);
    }
}


