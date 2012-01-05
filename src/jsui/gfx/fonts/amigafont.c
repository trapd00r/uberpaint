/* afdump
 *
 *  Dump out an amiga font file
 *
 *   Scott Lawrence
 *   2005-Feb-18
 *
 *   0.01: 2005-Feb-20	basic implementation
 *   0.02: 2005-Feb-21  fixed vertical spacings
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amigafont.h"
#include "endian.h"
#include "myfont.h"


void printbit( int bit, int bl )
{
    if( bit ) printf( "*" );
    else
	if( bl ) printf( "-" );
	else	 printf( "." );
}

int widthof( MY_FONT * fd, int c )
{
    int r = (fd->spacedata[c] & 0x00ffff) + fd->kerndata[c];
    if( r < fd->widthdata[c]) return fd->widthdata[c];
    return r;
}

/* vert dump */
void banner_dc( MY_FONT * fd, int c )
{
    int w, x, y;
    int start, end;

    if( !fd ) return;

    start = fd->spacedata[c] >> 16;
    end   = start + (fd->spacedata[c] & 0x00ffff);

    for( x=start, w=0 ; x<end ; x++, w++ )
    {
	for( y=fd->height-1 ; y>=0 ; y-- )
	{
	    if( fd->chardata[y][x] )	printf( "##" );
	    else
		if( y==fd->baseline )	printf( "' " );
		else			printf( "  " );
	}
	printf("\n");
    }
    for( x=0 ; x<fd->kerndata[ c ] ; x++ )
    {
    	w++;
	printf("\n");
    }
    for( ; w<fd->widthdata[ c ] ; w++ )
    {
	printf("\n");
    }
}

void dumpchar( FILE * fp, MY_FONT * fd, int c, int hs, int scanlines )
{
    char buf[128];
    char nib[16];
    int start, end, w, x;
    int out = 0;
    int mask = 8;
    int y = 0;
    int nnibs = 0;

    buf[0] = '\0';

    w = fd->widthdata[c];
    start = fd->spacedata[c] >> 16;
    end = start + (fd->spacedata[c] & 0x00ffff);

    for( y=0 ; y<fd->height ; y++)
    {
	mask = 8;
	out = 0;
	nnibs = 0;
	for( x=start; x<end ; x++ )
	{
	    if( mask == 0 )
	    {
		nnibs++;
		sprintf( nib, "%01x", out );
		strcat( buf, nib );
		out = 0; mask=8;
	    }
	    if( fd->chardata[y][x] )
	    {
		out |= (0xff & mask);
	    }
	    mask >>= 1;
	}
	sprintf( nib, "%01x", out );
	strcat( buf, nib );
	nnibs++;
	if( nnibs&1 ) strcat( buf, "0" );

	fprintf( fp,  "%s\n", buf );
	if( hs == 2 )
	{
	    if( scanlines ) for( x=0 ; x<strlen(buf) ; x++ ) buf[x] = '0';
	    fprintf( fp,  "%s\n", buf );
	}
	buf[0] = '\0';
    }
}

void banner_ds( MY_FONT * fd, char * str )
{
    if( !fd || !str ) return;

    while( *str != '\0' )
	banner_dc( fd, *str++ );
}



void usage( char ** argv )
{
    printf( "\n" );
    printf( "Ami2BDF v0.01  2005-02-20  Scott Lawrence  amigafont@umlautllama.com\n" );
    printf( "\n" );
    printf( "Usage: %s <Amiga Font> <Foundry> <Font Family> <BDF File> [-[d|s|h]]\n", argv[0] );
    printf( "       d   enables double-height mode\n" );
    printf( "       s   enables scanline mode\n" );
    printf( "       h  	enables +1px extra height\n" );
    printf( "\n" );
}

int main( int argc, char **argv )
{
    int x, y, z, gdi;
    MY_FONT * fd = NULL;
    FILE * fontfile = NULL;
    FILE * bdffile = NULL;
    char * foundry = NULL;
    char * family = NULL;
    long cdata = 0l;
    long cloc = 0l;
    long cspace = 0l;
    long ckern = 0l;
    int style, flags;

    /* args */
    int hs = 1;
    int addheight = 0;
    int scanlines = 0;

    /* argv checking... */
    /* argc == 5: normal height */
    /* argc == 6: double height */
    if( argc == 6 )
	for( x=0 ; x<strlen( argv[5] ) ; x++ )
	{
	    if( argv[5][x] == 'h' ) addheight = 1;
	    if( argv[5][x] == 's' ) { scanlines = 1; hs = 2; }
	    if( argv[5][x] == 'd' ) hs = 2;
	}
    else if( argc == 5 ) {
	/* no extra args; default values */
    } else {
	usage( argv );
	return( -1 );
    }


    /* try to open the input file */
    fontfile = fopen( argv[1], "r" );
    if( !fontfile ) {
	fprintf( stderr, "%s: Cannot open for input.\n", argv[1] );
	return( -2 );
    }

    foundry = argv[2];
    family = argv[3];

    /* try to open the output file */
    bdffile = fopen( argv[4], "w" );
    if( !bdffile ) {
	fclose( fontfile );
	fprintf( stderr, "%s: Cannot open for output.\n", argv[4] );
	return( -22 );
    }

    /* create the font struct.. */
    fd = myFont_new();
    if (!fd)
    {
	fclose( fontfile );
	fclose( bdffile );
	fprintf( stderr, "Memory allocation error. (-3)\n" );
	return( -3 ); 
    };


    /* load the header to MY_FONT structure */
    fd->height = littleEndianRead16_at( fontfile, F_YSIZE );  /* w  y size */
    fd->width = littleEndianRead16_at( fontfile, F_XSIZE );  /* w  x size */
    fd->baseline = littleEndianRead16_at( fontfile, F_BASELINE );  /* w  baseline */
    fd->lowChar = 0x00ff & littleEndianRead8_at( fontfile, F_LOWCHAR );  /* b  low char */
    fd->highChar =  0x00ff & littleEndianRead8_at( fontfile, F_HIGHCHAR );  /* b  high char */

    /* some locals to hold metadata we'll use to fill in the MY_FONT struct */
    fd->cd_width = littleEndianRead16_at( fontfile, F_MODULO );
    ckern  = F_OFFSET + littleEndianRead32_at( fontfile, F_CKERN );
    cspace = F_OFFSET + littleEndianRead32_at( fontfile, F_CSPACE );
    cloc   = F_OFFSET + littleEndianRead32_at( fontfile, F_CLOC );
    cdata  = F_OFFSET + littleEndianRead32_at( fontfile, F_CDATA );

    style = littleEndianRead8_at( fontfile, F_STYLE );
    if( style & STYLE_UNDERLINED ) 	printf( "s> UNDERLINED\n" );
    if( style & STYLE_BOLD ) 		printf( "s> BOLD\n" );
    if( style & STYLE_ITALIC ) 		printf( "s> ITALIC\n" );
    if( style & STYLE_EXTENDED ) 	printf( "s> EXTENDED\n" );
    if( style & STYLE_10 ) 		printf( "s> 10\n" );
    if( style & STYLE_20 ) 		printf( "s> 20\n" );
    if( style & STYLE_COLORFONT ) 	printf( "s> COLOR_FONT\n" ); 
    if( style & STYLE_TAGGED ) 		printf( "s> TAGGED\n" );

    flags = littleEndianRead8_at( fontfile, F_FLAGS );
    if( flags & FLAGS_ROMFONT ) 	printf( "f> ROMFONT\n" );
    if( flags & FLAGS_DISKFONT ) 	printf( "f> DISKFONT\n" );
    if( flags & FLAGS_REVPATH ) 	printf( "f> REVPATH\n" );
    if( flags & FLAGS_TALLDOT ) 	printf( "f> TALLDOT\n" );
    if( flags & FLAGS_WIDEDOT ) 	printf( "f> WIDEDOT\n" );
    if( flags & FLAGS_PROPORTIONAL ) 	printf( "f> PROPORTIONAL\n" );
    if( flags & FLAGS_DESIGNED ) 	printf( "f> DESIGNED\n" );
    if( flags & FLAGS_REMOVED ) 	printf( "f> REMOVED\n" );

    /* set up the ram in the structure */
    if( myFont_configMem( fd ))
    {
        fclose( fontfile );
        fclose( bdffile );
        myFont_Free( fd );
        return( -4 );
    }

    /* load other crap here. */
    printf( "   range: %x - %x (%c - %c)\n",
		fd->lowChar, fd->highChar, fd->lowChar, fd->highChar );
    printf( "   width: %d\n", fd->width );
    printf( "  height: %d\n", fd->height );
    printf( "baseline: %d\n", fd->baseline );
    printf( "  vscale: %d\n", hs );

/*
    printf( "\n" );

    printf( "    cdata: %08lx\n", cdata );
    printf( "   modulo: %08lx\n", fd->cd_width );

    printf( "    ckern: %08lx\n", ckern );
    printf( "   cspace: %08lx\n", cspace );
    printf( "     cloc: %08lx\n", cloc );
*/

    printf( "\n" );
    printf( "  Foundry: %s\n", foundry );
    printf( "   Family: %s\n", family );

    /* fill in the widthdata */
    if( ckern > 0x20 )
    {
	fseek( fontfile, cspace, SEEK_SET );
	for( x=fd->lowChar ; x<fd->highChar ; x++ )
	    fd->widthdata[x] = littleEndianRead16( fontfile );
    }

    /* fill in the spacedata */
    fseek( fontfile, cloc, SEEK_SET );
    for( x=fd->lowChar ; x<fd->highChar ; x++ )
	fd->spacedata[x] = littleEndianRead32( fontfile );

    /* fill in the kerndata */
    if( ckern > 0x20 )
    {
	fseek( fontfile, ckern, SEEK_SET );
	for( x=fd->lowChar ; x<fd->highChar ; x++ )
	{
	    fd->kerndata[x] = littleEndianRead16( fontfile );
	}
    }

    /* unpack the font data */
    gdi=0; /* index into glyph data array */
    for( y=0 ; y<fd->height ; y++ )
    {
	fseek( fontfile, cdata + (y*fd->cd_width), SEEK_SET );
	gdi = 0;
	for( x=0 ; x<(fd->cd_width) ; x++ )
	{
	    z = littleEndianRead8( fontfile );
	    fd->chardata[y][gdi++] = (z&0x80)?1:0;
	    fd->chardata[y][gdi++] = (z&0x40)?1:0;
	    fd->chardata[y][gdi++] = (z&0x20)?1:0;
	    fd->chardata[y][gdi++] = (z&0x10)?1:0;
	    fd->chardata[y][gdi++] = (z&0x08)?1:0;
	    fd->chardata[y][gdi++] = (z&0x04)?1:0;
	    fd->chardata[y][gdi++] = (z&0x02)?1:0;
	    fd->chardata[y][gdi++] = (z&0x01)?1:0;
	}
    }

/*
    banner_ds( fd, "My name is Scott and I really enjoy cheese!" );
    banner_ds( fd, "Burrito" );
*/


    fprintf( bdffile, "STARTFONT 2.1\n" );
    fprintf( bdffile, "COMMENT\n" );
    fprintf( bdffile, "COMMENT Created by\n" );
    fprintf( bdffile, "COMMENT             Ami2Bdf v0.02\n" );
    fprintf( bdffile, "COMMENT\n" );
    fprintf( bdffile, "COMMENT             Scott Lawrence    amigafont@umlautllama.com\n" );   
    fprintf( bdffile, "COMMENT                               http://www.umlautllama.com\n" );   
    fprintf( bdffile, "COMMENT\n" );

/* XLFD */
    fprintf( bdffile, "FONT -%s-%s%s%s-medium-%c-normal-",
		foundry, family, 
		(scanlines==1)?" scanline":(hs==2)?" double":" normal",
		(addheight==1)?" 1h":"",
		(style & STYLE_ITALIC)?'I':'R' );
    fprintf( bdffile, "-%d--96-96-%c-70-winsys\n",
		fd->height * hs, 
		(flags & FLAGS_PROPORTIONAL)?'P':'M' );

    fprintf( bdffile, "SIZE %d 96 96\n", fd->height * hs );
    fprintf( bdffile, "FONTBOUNDINGBOX %d %d %d %d\n", 
		fd->width, fd->height * hs,
		0, (fd->height - fd->baseline)*-1 * hs );

    fprintf( bdffile, "STARTPROPERTIES 3\n" );
	if( !addheight )
	{
	    /* normal */
	    if( hs == 1 )
	    {
		fprintf( bdffile, "FONT_DESCENT %d\n", (fd->height - fd->baseline) * hs );
		fprintf( bdffile, "FONT_ASCENT  %d\n", (fd->baseline) * hs );
	    } else {
		fprintf( bdffile, "FONT_DESCENT %d\n", (fd->height - fd->baseline-1) * hs );
		fprintf( bdffile, "FONT_ASCENT  %d\n", (fd->baseline+1) * hs );
	    }
	} else {
	    /* extra space */
	    fprintf( bdffile, "FONT_DESCENT %d\n", (fd->height - fd->baseline) * hs );
	    fprintf( bdffile, "FONT_ASCENT  %d\n", (fd->baseline +1) * hs );
	}

	/* fprintf( bdffile, "CAP_HEIGHT  %d\n", fd->baseline * hs ); */
	fprintf( bdffile, "DEFAULTCHAR  8192\n" );
    fprintf( bdffile, "ENDPROPERTIES\n" );

    fprintf( bdffile, "CHARS %d\n", fd->highChar - fd->lowChar + 1);
    y=0;
    for( x=fd->lowChar ; x<=fd->highChar ; x++ )
    {
	fprintf( bdffile, "STARTCHAR %d\n", y++ );
	fprintf( bdffile, "ENCODING  %d\n", x );
	fprintf( bdffile, "SWIDTH    %d 0\n", widthof( fd, x ) * 1000 );
	fprintf( bdffile, "DWIDTH    %d 0\n", widthof( fd, x ));
	fprintf( bdffile, "BBX       %d %d %d %d\n",
			widthof( fd, x ), fd->height * hs, 0, 
			-1 * ( fd->height - fd->baseline ));
	fprintf( bdffile, "BITMAP\n" );
	dumpchar( bdffile, fd, x, hs, scanlines );
	fprintf( bdffile, "ENDCHAR\n" );
    }


    fprintf( bdffile, "ENDFONT\n");

    fclose( fontfile );
    fclose( bdffile );
    myFont_Free( fd );
    return( 0 );
}
