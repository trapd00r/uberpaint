/* ini.c
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


#ifdef SunOS
#include <strings.h> /* for strtok */
char *strtok_r(char *s1, const char *s2, char **lasts);
#endif
#include <string.h>  /* for strlen */
#include <ctype.h>   /* for isspace */

/*
 * jstr_NullFirstC
 *
 *  nulls out the first occurrance of 'c'
 */
char * jstr_NullFirstC( char * buf, int max, char c )
{
    int x;
    if (!buf) return( buf );

    for( (x = 0) ; 
	 (buf[x] != '\0') && (x < max) ; 
         (x++) )
    {
   	if (buf[x] == c )
	{
	    buf[x] = '\0';
	} 
    }
    return( buf );
}

/* 
 * jstr_ZotLeadTrailSpace
 *
 *  converts something like "   hello there   " into "hello there"
 */
char * jstr_ZotLeadTrailSpace( char * buf, int max )
{
    int x, y;
    int len = strlen( buf );

    if (!buf) return( buf );
    if (len > max) return( buf );
    
    /* first walk from the end of the string back to the first non-zero */
    for ( (x = len-1) ;
	  (x > 0) && 
		(isspace((int)buf[x]) ||
		/* linux apparantly needs these next two to work correctly */
		(buf[x] <= ' ') || (buf[x] > '~')) ;
	  (x--) )
    {
	buf[x] = '\0';
    }

    /* now start at 0, and zot the leading space */
    for ( (x=0) ;
	  (x < max) && 
		( isspace((int)buf[x])  ||
		/* linux apparantly needs these next two to work correctly */
		(buf[x] <= ' ') || (buf[x] > '~')) ;
	  (x++) )
	/* do nothing */;

    y = 0;
    for ( ;
	  (x < max) && (buf[x] != '\0') ;
	  (x++) )
    {
	buf[y++] = buf[x];
    }
    buf[y] = '\0';

    return( buf );
}

/*
 * jstr_FindC
 *
 *  finds the first occurrance of 'C' after index 'start'
 */
int jstr_FindC( char * buf, int max, char c, int start )
{
    int x;
    if(!buf) return( -1 );

    if (start > strlen( buf )) return( -1 );

    if (start < 0) start = 0;

    for( (x = start) ;
	 (x<max) && (buf[x] != '\0') ; 
	 (x++) )
    {
	if (buf[x] == c) return x;
    }
    return -1;
}

#define IBLEN (1024)
char internalBuf[IBLEN];

/*
 * jstr_ArrayYoink
 *
 *  gets the [n]th element from the string passed in.
 *  string returned should not be free'd.  if the index was invalid, 
 *  it returns a NULL.
 */
char * jstr_ArrayYoink( char * buf, int index )
{
    int c = 0;
    char * word;
    char * sep = "\t\n\r ";

    if (!buf || index < 0)
	return( NULL );

    (void)strncpy( internalBuf, buf, IBLEN );

    for( word = strtok( internalBuf, sep ) ; 
	 word  &&  (c != index) ; 
	 word = strtok( NULL, sep ), c++ )
	/* do nothing */;

    return( word );
}
