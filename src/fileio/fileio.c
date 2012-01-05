/*
 * fileio
 *
 *  the basic routines to convert 'pages' out to 'images' for the jpnm library
 *  in the future any other file io routines will be in here as well.
 *  ie:
 *	loading / saving palettes
 *	loading / saving animations
 *	calling registered callbacks if another filetype is desired
 *	perhaps we also will use the Image Magick library here...
 */

/*
 * 4p - Pixel Pushing Paint Program
 * Copyright (C) 2000 Scott "Jerry" Lawrence
 *                    jsl.4p@absynth.com
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsui.h"
#include "fileio.h"
#include "iff/iffio.h"

char bakbase[] = BACKUP_PIC_NAME;

/* loaders and savers */
CFAPI fileio_loadersSavers[] = {
	NULL
};

/* exporters only */
CFAPI fileio_exporters[] = {
	NULL
};



IPAGE * 
file_load_page(
	char * filename
)
{
    if (file_is_iff(filename))
    {
	return( iff_file_load_page(filename) );
    }

    return NULL;

//    return( ppm_file_load_page(filename) );
}



void
file_backup(
	char * filename
)
{
    int pos, bytesread;
    char fbuf[1024];
    FILE * inf;
    FILE * otf;
    char * bakname = (char *) malloc (strlen(filename) + strlen(bakbase) +1);

    bakname = strcpy(bakname, filename);

    for (pos = strlen(bakname) ; pos > 0 && bakname[pos] != '/' ; pos--);

    if (bakname[pos] == '/')
    {
	bakname[pos+1] = '\0';
    } else {
	bakname[pos] = '\0';
    }

    bakname = strcat(bakname, bakbase);

    inf = fopen (filename, "r");
    if (inf != NULL)
    {
	otf = fopen (bakname, "w");
	do
	{
	    bytesread = fread(fbuf, 1, 1024, inf);
	    if (bytesread) fwrite(fbuf, 1, bytesread, otf);
	} while (bytesread);

	fclose(otf);
	fclose(inf);
    }

    free(bakname);
}

void
c_file_save_page(IPAGE * page, char * filename)
{
    FILE * fp;
    int linepos = 100;
    int xx;

    fp = fopen( filename, "w" );
    if (!fp) return;

    fprintf(fp, "int buffer_w = %d;\n", page->w);
    fprintf(fp, "int buffer_h = %d;\n", page->h);
    fprintf(fp, "int buffer_data[] = {");
    
    linepos = page->w + 3;

    for (xx=0 ; xx< page->h * page->w ; xx++)
    {
	if( linepos > 20)
	{
	    linepos = 0;
	    fprintf(fp, "\n    ");
	}
	fprintf(fp, "%d", page->pimage[xx]);
	if ( xx != (page->h * page->w) -1)
	    fprintf(fp, ", ");
	linepos++;
    }
    fprintf(fp, "\n};\n");
    fclose(fp);
}

void
file_save_page(
	IPAGE * page,
	char * filename
)
{
    if (!page || !filename) return;

    file_backup(filename);
    
    c_file_save_page(page, filename);
    //iff_file_save_page(page, filename);
    //ppm_file_save_page(page, filename);
}

