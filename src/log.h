/*
** log.h
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

#define LOG_LEVEL_UNDEFINED	(0)
#define LOG_LEVEL_DEBUG		(1)
#define LOG_LEVEL_WARNING	(2)
#define LOG_LEVEL_ERROR		(3)
#define LOG_LEVEL_INFO		(4)

char * log_type_to_str( int type );


void log_str( int type, char * text );

#define LOG_DEBUG( A )		log_str( LOG_LEVEL_DEBUG, (A) )
#define LOG_WARNING( A )	log_str( LOG_LEVEL_WARNING, (A) )
#define LOG_ERROR( A )		log_str( LOG_LEVEL_ERROR, (A) )
#define LOG_INFO( A )		log_str( LOG_LEVEL_INFO, (A) )
