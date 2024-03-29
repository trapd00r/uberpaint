/*         ______   ___    ___
 *        /\  _  \ /\_ \  /\_ \
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \/___/
 *
 *      Main header file for the Allegro library.
 *      This should be included by everyone and everything.
 *
 *      By Shawn Hargreaves.
 *
 *      See readme.txt for copyright information.
 */


#ifndef ALLEGRO_H
#define ALLEGRO_H

#ifdef __cplusplus
   extern "C" {
#endif

// stuff removed

#define AL_FUNC(type, name, args)               type name args
#define AL_FUNCPTR(type, name, args)            extern type (*name) args
#define AL_METHOD(type, name, args)             type (*name) args



/***************************************/
/************ GUI routines  ************/
/***************************************/

typedef struct DIALOG 
{
   AL_METHOD(int, proc, (int, struct DIALOG *, int ));
   int x, y, w, h;               /* position and size of the object */
   int fg, bg;                   /* foreground and background colors */
   int key;                      /* keyboard shortcut (ASCII code) */
   int flags;                    /* flags about the object state */
   int d1, d2;                   /* any data the object might require */
   void *dp, *dp2, *dp3;         /* pointers to more object data */
} DIALOG;


/* a popup menu */
typedef struct MENU
{
   char *text;                   /* menu item text */
   AL_METHOD(int, proc, (void)); /* callback function */
   struct MENU *child;           /* to allow nested menus */
   int flags;                    /* flags about the menu state */
   void *dp;                     /* any data the menu might require */
} MENU;


/* stored information about the state of an active GUI dialog */
typedef struct DIALOG_PLAYER
{
   int obj;
   int res;
   int mouse_obj;
   int focus_obj;
   int joy_on;
   int click_wait;
   int mouse_ox, mouse_oy;
   int mouse_oz;
   int mouse_b;
   DIALOG *dialog;
} DIALOG_PLAYER;


/* bits for the flags field */
#define D_EXIT          1        /* object makes the dialog exit */
#define D_SELECTED      2        /* object is selected */
#define D_GOTFOCUS      4        /* object has the input focus */
#define D_GOTMOUSE      8        /* mouse is on top of object */
#define D_HIDDEN        16       /* object is not visible */
#define D_DISABLED      32       /* object is visible but inactive */
#define D_DIRTY         64       /* object needs to be redrawn */
#define D_INTERNAL      128      /* reserved for internal use */
#define D_USER          256      /* from here on is free for your own use */


/* return values for the dialog procedures */
#define D_O_K           0        /* normal exit status */
#define D_CLOSE         1        /* request to close the dialog */
#define D_REDRAW        2        /* request to redraw the dialog */
#define D_REDRAWME      4        /* request to redraw this object */
#define D_WANTFOCUS     8        /* this object wants the input focus */
#define D_USED_CHAR     16       /* object has used the keypress */


/* messages for the dialog procedures */
#define MSG_START       1        /* start the dialog, initialise */
#define MSG_END         2        /* dialog is finished - cleanup */
#define MSG_DRAW        3        /* draw the object */
#define MSG_CLICK       4        /* mouse click on the object */
#define MSG_DCLICK      5        /* double click on the object */
#define MSG_KEY         6        /* keyboard shortcut */
#define MSG_CHAR        7        /* other keyboard input */
#define MSG_UCHAR       8        /* unicode keyboard input */
#define MSG_XCHAR       9        /* broadcast character to all objects */
#define MSG_WANTFOCUS   10       /* does object want the input focus? */
#define MSG_GOTFOCUS    11       /* got the input focus */
#define MSG_LOSTFOCUS   12       /* lost the input focus */
#define MSG_GOTMOUSE    13       /* mouse on top of object */
#define MSG_LOSTMOUSE   14       /* mouse moved away from object */
#define MSG_IDLE        15       /* update any background stuff */
#define MSG_RADIO       16       /* clear radio buttons */
#define MSG_WHEEL       17       /* mouse wheel moved */
#define MSG_LPRESS      18       /* mouse left button pressed */
#define MSG_LRELEASE    19       /* mouse left button released */
#define MSG_MPRESS      20       /* mouse middle button pressed */
#define MSG_MRELEASE    21       /* mouse middle button released */
#define MSG_RPRESS      22       /* mouse right button pressed */
#define MSG_RRELEASE    23       /* mouse right button released */
#define MSG_USER        24       /* from here on are free... */


/* some dialog procedures */
AL_FUNC(int, d_yield_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_clear_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_box_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_shadow_box_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_bitmap_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_text_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_ctext_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_rtext_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_button_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_check_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_radio_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_icon_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_keyboard_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_edit_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_list_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_text_list_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_textbox_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_slider_proc, (int msg, DIALOG *d, int c));
AL_FUNC(int, d_menu_proc, (int msg, DIALOG *d, int c));

AL_VAR(DIALOG *, active_dialog);
AL_VAR(MENU *, active_menu);

AL_VAR(int, gui_mouse_focus);

AL_VAR(int, gui_fg_color);
AL_VAR(int, gui_mg_color);
AL_VAR(int, gui_bg_color);

AL_VAR(int, gui_font_baseline);

AL_FUNCPTR(int, gui_mouse_x, (void));
AL_FUNCPTR(int, gui_mouse_y, (void));
AL_FUNCPTR(int, gui_mouse_z, (void));
AL_FUNCPTR(int, gui_mouse_b, (void));

AL_FUNC(int, gui_textout, (BITMAP *bmp, AL_CONST char *s, int x, int y, int color, int centre));
AL_FUNC(int, gui_strlen, (AL_CONST char *s));
AL_FUNC(void, position_dialog, (DIALOG *dialog, int x, int y));
AL_FUNC(void, centre_dialog, (DIALOG *dialog));
AL_FUNC(void, set_dialog_color, (DIALOG *dialog, int fg, int bg));
AL_FUNC(int, find_dialog_focus, (DIALOG *dialog));
AL_FUNC(int, offer_focus, (DIALOG *d, int obj, int *focus_obj, int force));
AL_FUNC(int, dialog_message, (DIALOG *dialog, int msg, int c, int *obj));
AL_FUNC(int, broadcast_dialog_message, (int msg, int c));
AL_FUNC(int, do_dialog, (DIALOG *dialog, int focus_obj));
AL_FUNC(int, popup_dialog, (DIALOG *dialog, int focus_obj));
AL_FUNC(DIALOG_PLAYER *, init_dialog, (DIALOG *dialog, int focus_obj));
AL_FUNC(int, update_dialog, (DIALOG_PLAYER *player));
AL_FUNC(int, shutdown_dialog, (DIALOG_PLAYER *player));
AL_FUNC(int, do_menu, (MENU *menu, int x, int y));
AL_FUNC(int, alert, (AL_CONST char *s1, AL_CONST char *s2, AL_CONST char *s3, AL_CONST char *b1, AL_CONST char *b2, int c1, int c2));
AL_FUNC(int, alert3, (AL_CONST char *s1, AL_CONST char *s2, AL_CONST char *s3, AL_CONST char *b1, AL_CONST char *b2, AL_CONST char *b3, int c1, int c2, int c3));
AL_FUNC(int, file_select, (AL_CONST char *message, char *path, AL_CONST char *ext));
AL_FUNC(int, gfx_mode_select, (int *card, int *w, int *h));
AL_FUNC(int, gfx_mode_select_ex, (int *card, int *w, int *h, int *color_depth));



/*****************************************/
/************ Helper includes ************/
/*****************************************/

#include "allegro/alinline.h"

#ifdef ALLEGRO_EXTRA_HEADER
   #include ALLEGRO_EXTRA_HEADER
#endif


#ifdef __cplusplus
   }
#endif

#endif          /* ifndef ALLEGRO_H */


