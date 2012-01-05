/*
 * color
 * 
 *   color tools callback handlers
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
#include "cursors.h"
#include "dialogs.h"


////////////////////////////////////////////////////////////////////////////////
// palette

void
tools_palette_fg_set (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	page_active->fgpen->Icolor = keyhit;
	Page_Copy_Pens(page_rubberband, page_active);
    }
}

void
tools_palette_bg_set (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	page_active->bgpen->Icolor = keyhit;
	Page_Copy_Pens(page_rubberband, page_active);
    }
}

void
tools_palette_fg_increment (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	page_active->fgpen->Icolor++;
	if (page_active->fgpen->Icolor >= page_active->ncolors)
	{
	    page_active->fgpen->Icolor = 0;
	}
	Page_Copy_Pens(page_rubberband, page_active);
	jsui_dialog_broadcast(PAINT_MSG_FGPALETTESET, 
				page_active->fgpen->Icolor);
    }
}

void
tools_palette_fg_decrement (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	page_active->fgpen->Icolor--;
	if (page_active->fgpen->Icolor < 0)
	{
	    page_active->fgpen->Icolor = page_active->ncolors -1;
	}
	Page_Copy_Pens(page_rubberband, page_active);
	jsui_dialog_broadcast(PAINT_MSG_FGPALETTESET, 
				page_active->fgpen->Icolor);
    }
}


void
tools_palette_bg_increment (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	page_active->bgpen->Icolor++;
	if (page_active->bgpen->Icolor >= page_active->ncolors)
	{
	    page_active->bgpen->Icolor = 0;
	}
	Page_Copy_Pens(page_rubberband, page_active);
	jsui_dialog_broadcast(PAINT_MSG_BGPALETTESET, 
				page_active->bgpen->Icolor);
    }
}

void
tools_palette_bg_decrement (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	page_active->bgpen->Icolor--;
	if (page_active->bgpen->Icolor < 0)
	{
	    page_active->bgpen->Icolor = page_active->ncolors -1;
	}
	Page_Copy_Pens(page_rubberband, page_active);

	jsui_dialog_broadcast(PAINT_MSG_BGPALETTESET, 
				page_active->bgpen->Icolor);
    }
}

void
tools_eyedropper (
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    switch (mouse_event)
    {
	case (TOOL_EVENT_INIT):
	    Page_Negative(page_rubberband);
	    CURSOR_EYEDROPPER();
	    LOG_DEBUG("eyedropper");
	    break;

	case (TOOL_EVENT_RELEASE):
	    if (mouse_buttons == 1)
	    {
		page_active->fgpen->Icolor = 
				primitive_pixel_get(page_active, x, y);
		jsui_dialog_broadcast(PAINT_MSG_FGPALETTESET, 
					page_active->fgpen->Icolor);
	    } else if (mouse_buttons == 3) {
		page_active->bgpen->Icolor = 
				primitive_pixel_get(page_active, x, y);
		jsui_dialog_broadcast(PAINT_MSG_BGPALETTESET, 
					page_active->bgpen->Icolor);
	    }
	    Page_Copy_Pens(page_rubberband, page_active);
	    tool_previous_mode();
	    break;

	default:
	    break;

    }
}


////////////////////////////////////////////////////////////////////////////////


void 
tools_toggle_cycle(
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	color_cycle = (color_cycle)?0:1;
	if( color_cycle )
		LOG_DEBUG( "color cycle ON" );
	else
		LOG_DEBUG( "color cycle OFF" );
    }
}


////////////////////////////////////////////////////////////////////////////////

void 
tools_palette_edit(
	int mouse_event,
	int mouse_buttons,
	int keyhit,
	int x,
	int y
)
{
    if (mouse_event == TOOL_EVENT_INIT)
    {
	LOG_DEBUG( "Palette Editor" );
	jsui_dialog_run_modal( palette_edit_dialog );
    }
}
