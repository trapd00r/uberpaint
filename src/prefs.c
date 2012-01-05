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
#define _SYS_WAIT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jsui.h"
#include "version.h"
#include "strings.h"
#include "prefs.h"


USER_PREFS userPrefs;


void prefs_defaults( void )
{
	userPrefs.displayHelp = PREFS_NO;
	userPrefs.debug = PREFS_NO;
	userPrefs.primaryFile = NULL;
	userPrefs.secondaryFile = NULL;
	userPrefs.screenWidth = 640;
	userPrefs.screenHeight = 400;
	userPrefs.screenSize = PREFS_NO;
	userPrefs.fullscreen = PREFS_NO;
	userPrefs.imageWidth = 320;
	userPrefs.imageHeight = 200;
	userPrefs.imageSize = PREFS_NO;
	userPrefs.quick = PREFS_NO;
}


void prefs_usage( char * exename )
{
	printf( "UberPaint 4P  by Scott Lawrence  4p@umlautllama.com\n" );
	printf( "   Version %s (%s) (%s)\n", 
			STRINGS_4P, J_VERSION, J_REVISION, J_TPOTC );
	printf( "Usage:\n" );
	printf( "   %s [options]\n", exename );
	printf( "Options:\n" );
	printf( "\t-help           \tDisplay this help message\n" );
	printf( "\t-img0 FILE      \tload FILE as the primary image\n" );
	printf( "\t-img1 FILE      \tload FILE as the secondary image\n" );
	printf( "\t-imageres W H   \tSelect a image res of W by H\n" );
	printf( "\t-screenres W H  \tSelect a screen res of W by H\n" );
	printf( "\t-fullscreen     \tDisplay on the entire screen\n" );
	printf( "\t-quick          \tLoad up quick, without prompts\n" );
	printf( "\t-debug          \tEnable debugging options and output\n" );
}


int prefs_args_token( char * txt )
{
	if( !txt ) return( PREFS_UNKNOWN );
	if( strlen( txt ) < 2 ) return( PREFS_UNKNOWN );

	if( !strcasecmp( txt, "-help" )) return( PREFS_HELP );
	if( !strcasecmp( txt, "-h" )) return( PREFS_HELP );
	if( !strcasecmp( txt, "-v" )) return( PREFS_HELP );
	if( !strcasecmp( txt, "-version" )) return( PREFS_HELP );

	if( !strcasecmp( txt, "-debug" )) return( PREFS_DEBUG );

	if( !strcasecmp( txt, "-imageres" )) return( PREFS_IMAGERES );
	if( !strcasecmp( txt, "-img0" )) return( PREFS_PRIMARY );
	if( !strcasecmp( txt, "-img1" )) return( PREFS_SECONDARY );

	if( !strcasecmp( txt, "-screenres" )) return( PREFS_SCREENRES );
	if( !strcasecmp( txt, "-fullscreen" )) return( PREFS_FULLSCREEN );

	if( !strcasecmp( txt, "-q" )) return( PREFS_QUICK );
	if( !strcasecmp( txt, "-quick" )) return( PREFS_QUICK );

	return( PREFS_UNKNOWN );
}


int prefs_args_parse( int argc, char *argv[] )
{
	int a = 0;

	prefs_defaults();

	while( ++a < argc ) {
		switch( prefs_args_token( argv[a] )) {
		case( PREFS_HELP ):
			userPrefs.displayHelp = PREFS_YES;
			break;

		case( PREFS_DEBUG ):
			userPrefs.debug = PREFS_YES;
			break;

		case( PREFS_PRIMARY ):
			userPrefs.primaryFile = argv[ ++a ];
			break;

		case( PREFS_SECONDARY ):
			userPrefs.secondaryFile = argv[ ++a ];
			break;

		case( PREFS_FULLSCREEN ):
			userPrefs.fullscreen = PREFS_YES;
			break;

		case( PREFS_QUICK ):
			userPrefs.quick = PREFS_YES;
			break;

		case( PREFS_IMAGERES ):
			userPrefs.imageWidth = atoi( argv[ ++a ] );
			userPrefs.imageHeight = atoi( argv[ ++a ] );
			userPrefs.imageSize = PREFS_YES;
			break;

		case( PREFS_SCREENRES ):
			userPrefs.screenWidth = atoi( argv[ ++a ] );
			userPrefs.screenHeight = atoi( argv[ ++a ] );
			userPrefs.screenSize = PREFS_YES;
			break;

		case( PREFS_UNKNOWN ):
		default:
			break;
		}
	}

	if( userPrefs.displayHelp == PREFS_YES ) {
		prefs_usage( argv[0] );
		return( PREFS_EXIT );
	}

	return( PREFS_CONTINUE );
}
