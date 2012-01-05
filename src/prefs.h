/*
** prefs.c
**
**  user preferences and command line argument parser
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

typedef struct _USER_PREFS {
	int displayHelp;
	int debug;
	char * primaryFile;
	char * secondaryFile;
	int screenWidth;
	int screenHeight;
	int screenSize;
	int fullscreen;
	int imageWidth;
	int imageHeight;
	int imageSize;
	int quick;
} USER_PREFS;

extern USER_PREFS userPrefs;

#define PREFS_UNKNOWN		(0)
#define PREFS_HELP		(1)
#define PREFS_DEBUG		(2)
#define PREFS_PRIMARY		(3)
#define PREFS_SECONDARY		(4)
#define PREFS_SCREENRES		(5)
#define PREFS_IMAGERES		(6)
#define PREFS_QUICK		(7)
#define PREFS_FULLSCREEN	(8)

#define PREFS_CONTINUE		(0)
#define PREFS_EXIT		(1)

#define PREFS_YES		(1)
#define PREFS_NO		(0)


void prefs_defaults( void );
void prefs_usage( char * exename );

int prefs_args_token( char * txt );
int prefs_args_parse( int argc, char *argv[] );
