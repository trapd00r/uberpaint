/* myfont
 *
 *  routines for dealing with my font structure... 
 *
 *   Scott Lawrence
 *   2005-Feb-20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amigafont.h"
#include "endian.h"
#include "myfont.h"



/* allocate the ram */
MY_FONT * myFont_new( void )
{
    /* create the font struct.. */
    MY_FONT * fd = malloc( sizeof( MY_FONT ));
    if (!fd) return( NULL ); 

    /* initialize the struct elements... */
    fd->widthdata = NULL;
    fd->spacedata = NULL;
    fd->kerndata = NULL;
    fd->chardata = NULL;
    fd->lowChar = fd->highChar = 0;
    fd->width = fd->height = fd->baseline = 0;
    fd->cd_width = 0;

    return( fd );
}


/* set up the ram structures */
int myFont_configMem( MY_FONT * fd )
{
    int y;

    /* allocate chunks 'o ram for the MY_FONT struct */
    if( !(fd->widthdata = (int *) malloc( sizeof(int) * (fd->highChar+1)))){
	return( -4 );
    }
    memset( fd->widthdata, 0, sizeof(int) * (fd->highChar+1) );

    if( !(fd->spacedata = (int *) malloc( sizeof(int) * (fd->highChar+1)))){
	return( -5 );
    }
    memset( fd->spacedata, 0, sizeof(int) * (fd->highChar+1) );

    if( !(fd->kerndata = (int *) malloc( sizeof(int) * (fd->highChar+1)))){
	return( -6 );
    }
    memset( fd->kerndata, 0, sizeof(int) * (fd->highChar+1) );

    if( !(fd->chardata = (int **) malloc( sizeof(int *) * fd->height ))){
	return( -7 );
    }
    for( y=0 ; y<fd->height ; y++ ) fd->chardata[y] = NULL;

    for( y=0 ; y<fd->height ; y++ )
    {
	fd->chardata[y] = (int *) malloc( sizeof(int) * (fd->cd_width*8));
	if( !fd->chardata[y] )
	    return( -8 );
	memset( fd->chardata[y], 0, sizeof(int) * fd->cd_width*8 );
    }
    return( 0 );
}


/* release the ram */
void myFont_Free( MY_FONT * f )
{
    if( !f ) return;
    if( f->widthdata ) free( f->widthdata );
    if( f->spacedata ) free( f->spacedata );
    if( f->kerndata ) free( f->kerndata );
    if( f->chardata )
    {
	int x;
	for( x=0 ; x<f->height ; x++ )
	    if( f->chardata[x] ) free( f->chardata[x] );

	free( f->chardata );
    }
    /*free( f );*/
}
