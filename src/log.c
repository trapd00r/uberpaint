/*
** log.c
**
**  log textual output from the program
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
#include "dialogs.h"
#include "log.h"


char * log_type_to_str( int type )
{
	switch( type )
	{
	case( LOG_LEVEL_DEBUG ): 	return( STR_LK( STRINGS_DEBUG ) );
	case( LOG_LEVEL_WARNING ): 	return( STR_LK( STRINGS_WARNING ) );
	case( LOG_LEVEL_ERROR ): 	return( STR_LK( STRINGS_ERROR ) );
	case( LOG_LEVEL_INFO ): 	return( STR_LK( STRINGS_INFO ) );
	}
	return( STR_LK( STRINGS_UNKNOWN ) );
}

void log_str( int type, char * text )
{
	if( userPrefs.debug == PREFS_YES )
	{
		fprintf( stderr, "%10s: %s\n", log_type_to_str( type ), text );
		manager_status( text );
	}

	if(  	   (type == LOG_LEVEL_INFO)
		|| (type == LOG_LEVEL_WARNING)
		|| (type == LOG_LEVEL_ERROR)
	  ) {
		manager_status( text );
	}
}
