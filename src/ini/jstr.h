/* jstr.h
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


/*
 * jstr_NullFirstC
 *
 *  nulls out the first occurrance of 'c'
 */
char * jstr_NullFirstC( char * buf, int max, char c );

/* 
 * jstr_ZotLeadTrailSpace
 *
 *  converts something like "   hello there   " into "hello there"
 */
char * jstr_ZotLeadTrailSpace( char * buf, int max );

/*
 * jstr_FindC
 *
 *  finds the first occurrance of 'C' after index 'start'
 */
int jstr_FindC( char * buf, int max, char c, int start );

/*
 * jstr_ArrayYoink
 *
 *  gets the [n]th element from the string passed in.
 *  string returned should not be free'd.  if the index was invalid,
 *  it returns a NULL.
 */
char * jstr_ArrayYoink( char * buf, int index );
