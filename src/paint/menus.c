/*
 * menus
 *
 *   menu stuff
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
#include "menus.h"
#include "strings.h"


//////////////////////////////////////////////////////////////////////

JSUI_MENU menu_4p[] = 
{
    { STR_LK( STRINGS_ABOUT ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_BAR
    { STR_LK( STRINGS_PREFERENCES ), 	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_QUIT),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_file_flip[] =
{
    { STR_LK( STRINGS_HORIZ ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_VERT ), 		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_file_color[] =
{
    { STR_LK( STRINGS_PALETTE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_USEBRUSHPALETTE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_RESTOREPALETTE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_DEFAULTPALETTE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_CYCLE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_BGTOFG ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_BGBTOFG ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_REMAP ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_file_spare[] =
{
    { STR_LK( STRINGS_SWAP ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_COPYTOSPARE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_MERGEINFRONT ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_MERGEINBACK ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_DELETETHIS ),	menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_file[] = 
{
    { STR_LK( STRINGS_LOAD ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SAVE ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_BAR
    { STR_LK( STRINGS_FLIP ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_CHANGECOLOR ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SPARE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_PAGESIZE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SHOWPAGE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SCREENFORMAT ),	menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};



//////////////////////////////////////////////////////////////////////

JSUI_MENU menu_brush_size[] =
{
    { STR_LK( STRINGS_STRETCH ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_HALVE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_DOUBLE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_DOUBLEH ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_DOUBLEV ),	menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_brush_flip[] =
{
    { STR_LK( STRINGS_HORIZ ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_VERT ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_brush_outline[] =
{
    { STR_LK( STRINGS_OUTLINE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_TRIM ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_brush_rotate[] =
{
    { STR_LK( STRINGS_90DEG ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_ANYANGLE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SHEAR ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_brush_color[] =
{
    { STR_LK( STRINGS_BGTOFG ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_BGBTOFG ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_REMAP ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_TRANSPARENCY ),	menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_brush_bend[] =
{
    { STR_LK( STRINGS_HORIZ ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_VERT ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_brush_handle[] =
{
    { STR_LK( STRINGS_CENTER ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_CORNER ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_PLACE ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_brush[] =
{
    { STR_LK( STRINGS_LOAD ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SAVE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_RESTORE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SIZE ),		NULL, menu_brush_size, 0, NULL},
    { STR_LK( STRINGS_FLIP ),		NULL, menu_brush_flip, 0, NULL},
    { STR_LK( STRINGS_OUTLINE ),	NULL, menu_brush_outline, 0, NULL},
    { STR_LK( STRINGS_ROTATE ),		NULL, menu_brush_rotate, 0, NULL},
    { STR_LK( STRINGS_CHANGECOLOR ),	NULL, menu_brush_color, 0, NULL},
    { STR_LK( STRINGS_BEND ),		NULL, menu_brush_bend, 0, NULL},
    { STR_LK( STRINGS_HANDLE ),		NULL, menu_brush_handle, 0, NULL},
    JSUI_MENU_END
};

//////////////////////////////////////////////////////////////////////

JSUI_MENU menu_mode[] =
{
    { STR_LK( STRINGS_M_MATTE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_COLOR ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_REPLACE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_SMEAR ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_SHADE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_BLEND ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_CYCLE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_SMOOTH ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_TINT ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_M_HALFBRITE ),	menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

//////////////////////////////////////////////////////////////////////

JSUI_MENU menu_anim[] =
{
    { STR_LK( STRINGS_LOAD ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SAVE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_MOVE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_FRAMES ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_CONTROL ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_ANIMBRUSH ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_METHOD ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

//////////////////////////////////////////////////////////////////////

JSUI_MENU menu_effects_stencil[] =
{
    { STR_LK( STRINGS_LOAD ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_SAVE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_MAKE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_REMAKE ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_LOCKFG ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_REVERSE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_ONOFF ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_FREE ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_effects_background[] =
{
    { STR_LK( STRINGS_FIX ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_OFF ),		menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_effects[] =
{
    { STR_LK( STRINGS_STENCIL ),	NULL, menu_effects_stencil, 0, NULL},
    { STR_LK( STRINGS_BACKGROUND ),	NULL, menu_effects_background, 0, NULL},
    JSUI_MENU_END
};

//////////////////////////////////////////////////////////////////////

JSUI_MENU menu_font_style[] =
{
    { STR_LK( STRINGS_BOLD ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_ITALIC ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_UNDERLINE ),	menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

JSUI_MENU menu_font[] =
{
    { STR_LK( STRINGS_STYLE ),		NULL, menu_font_style, 0, NULL},
    { STR_LK( STRINGS_SCANFONTS ),	menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};

//////////////////////////////////////////////////////////////////////

JSUI_MENU menu_prefs[] =
{
    { STR_LK( STRINGS_COORDS ),		menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_MULTICYCLE ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_EXCLBRUSH ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_AUTOTRANS ),	menu_stub, NULL, 0, NULL},
    { STR_LK( STRINGS_AUTOGRID ),	menu_stub, NULL, 0, NULL},
    JSUI_MENU_END
};


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

JSUI_MENU menu_title[] =
{
    { STR_LK( STRINGS_4P ),		NULL, menu_4p, 0, NULL},
    { STR_LK( STRINGS_FILE ),		NULL, menu_file, 0, NULL},
    { STR_LK( STRINGS_BRUSH ),		NULL, menu_brush, 0, NULL},
    { STR_LK( STRINGS_MODE ),		NULL, menu_mode, 0, NULL},
    { STR_LK( STRINGS_ANIM ),		NULL, menu_anim, 0, NULL},
    { STR_LK( STRINGS_EFFECTS ),	NULL, menu_effects, 0, NULL},
    { STR_LK( STRINGS_FONT ),		NULL, menu_font, 0, NULL},
    { STR_LK( STRINGS_PREFS ),		NULL, menu_prefs, 0, NULL},
    JSUI_MENU_END
};
