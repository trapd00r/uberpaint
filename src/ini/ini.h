/* ini.h
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


typedef struct inistruct{
    char * group;               /* group name */
    char * key;                 /* the key name. */
    char * value;               /* the value */
    struct inistruct * next;    /* the next one in the list */
} INIStruct;


/*
 * ini_Destroy
 *
 * clears the internal structure
 */
void
ini_Destroy( INIStruct * i );


/*
 * ini_ParseFile
 *
 *   will parse in the file "filename" into the internal structures
 */
INIStruct *
ini_ParseFile( char * filename );


/*
 * ini_Query
 * 
 *  finds data from the internal strucutre.
 *  the returned data is a char string allocated internally.       
 *  do not free it externally!
 */
char *
ini_Query( INIStruct * i, char * group, char * key );


/*
 * ini_QueryInt
 * 
 *  finds data from the internal strucutre.
 *  the returned data is an int.
 */
int
ini_QueryInt( INIStruct * i, char * group, char * key );


/*
 * ini_QueryArrayString
 *
 * finds the n'th element in the array found via an INI query
 *  do not free it externally!
 */
char *
ini_QueryArrayString( INIStruct * i, char * group, char * key, int index );



/*
 * ini_QueryArrayInt
 *
 * finds the n'th element in the array found via an INI query
 *  do not free it externally!
 */
int
ini_QueryArrayInt( INIStruct * i, char * group, char * key, int index );


/*
 * ini_Dump
 *
 *  dump out the internal header list. (for debug use )
 */
void ini_Dump( INIStruct * i );
