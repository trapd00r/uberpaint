/* myfont
 *
 *  my internal font definition
 *
 *   Scott Lawrence
 *   2005-Feb-18
 */

typedef struct _my_font{
    int lowChar;            /* low character number			*/
    int highChar;           /* high character number			*/
    
    int width;              /* set to -1 if proportional		*/
    int height;             /* height of the font			*/
    int baseline;           /* where is the baseline			*/
    
    int * widthdata;        /* widths of each of the characters (cspaces)*/
    int * spacedata;        /* size of char + space  (cloc)		*/
    int * kerndata;         /* add horiz. when rendering (ckern)	*/

    int cd_width;	    /* width of each row below:			*/
    int ** chardata;        /* pointers to arrays of bytes.		*/
			    /* array of rows of (modulo) bytes		*/
} MY_FONT;

MY_FONT * myFont_new( void );
int myFont_configMem( MY_FONT * fd );

void myFont_Free( MY_FONT * f );

