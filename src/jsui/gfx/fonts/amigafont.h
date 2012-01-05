/* amigafont
 *
 *  Amiga font format definition.
 *  Support and descriptions included for standard bitmap fonts.
 *  Color fonts not supported/described yet, although notes are included.
 *
 *   Scott Lawrence
 *   2005-Feb-18
 */

/*
	The values contained here are absolute from the beginning
	of the font file.  I tried cross referencing the structures
	to the data in the files, and the structures don't seem to
	match up...  so rather than trying to parse the file into
	structures, I've instead gone with absolute positionings
	from the start of the file.
*/

#define F_YSIZE		(0x006e)	/* word - height */
#define F_STYLE		(0x0070)	/* byte */
#define   STYLE_NORMAL		(0x00)	/* normal text */
#define   STYLE_UNDERLINED	(0x01)	/* underlined under baseline */
#define   STYLE_BOLD		(0x02)	/* draw, x+1 draw */
#define   STYLE_ITALIC		(0x04)	/* slanted 1:2 right */
#define   STYLE_EXTENDED	(0x08)	/* wider than normal face */
#define   STYLE_10		(0x10)	/* - unknown - */
#define   STYLE_20		(0x20)	/* - unknown - */
#define	  STYLE_COLORFONT	(0x40)	/* ColorTextFont structure present */
#define   STYLE_TAGGED		(0x80)	/* TextAttr is TTextAttr */
#define F_FLAGS		(0x0071)	/* byte */
#define   FLAGS_ROMFONT		(0x01)	/* font is in rom (HA!) */
#define   FLAGS_DISKFONT	(0x02)	/* font is from diskfont.lib */
#define   FLAGS_REVPATH		(0x04)	/* draw right to left */
#define   FLAGS_TALLDOT		(0x08)	/* hires non-interlaced */
#define   FLAGS_WIDEDOT		(0x10)	/* lores interlaced */
#define   FLAGS_PROPORTIONAL	(0x20)	/* glyph width varies from nominal */
#define   FLAGS_DESIGNED	(0x40)	/* size designed (?) */
#define   FLAGS_REMOVED		(0x80)	/* font has been removed (?) */
#define F_XSIZE		(0x0072)	/* word - nominal width */
#define F_BASELINE	(0x0074)	/* word - top to baseline */
#define F_BOLDSMEAR	(0x0076)	/* word - smear for bold enhancement */
#define F_ACCESSORS	(0x0078)	/* word - ignore */
#define F_LOWCHAR	(0x007a)	/* byte - first glyph */
#define F_HIGHCHAR	(0x007b)	/* byte - last glyph */

    /* pointers, see below */
#define F_CDATA		(0x007c)	/* long   char data pointer */
#define F_MODULO	(0x0080)	/* word   nbytes per CDATA row */
#define F_CLOC		(0x0082)	/* long   char locations and widths */
#define F_CSPACE	(0x0086)	/* long   char width spaces */
#define F_CKERN		(0x008a)	/* long   char kerning additions */ 
#define F_OFFSET	(0x20)		/* add to above ptrs to make absolute */

/*
 * For absolute file positioning, I've found that adding 0x20 onto the
 * offsets contained in <F_CDATA>, <F_CLOC>, <F_CSPACE> and <F_CKERN>.
 * I would say that this is due to the DiskFont struct header, but that
 * doesn't add up properly... Instead, add <F_OFFSET> on, and the pointers
 * become offsets from the start of the file.
 *
 * The <F_CDATA> pointer points to an array of bytes of glyph bitmap data.
 * There are <F_MODULO> bytes of data, horizontally, containing the top row
 * of all of the glyphs.  There are <F_YSIZE>s of these rows, one for 
 * each row of pixels in the glyph's height.
 *
 *  .@@@@. @@@@. .@@@. @@@@. @@@@@@@@ ...
 *  @....@ @...@ @...@ @...@ @@....@@ ...
 *  @@@@@@ @@@@. @.... @...@ @@....@@ ...
 *  @....@ @...@ @.... @...@ @@....@@ ...
 *  @....@ @...@ @...@ @...@ @@....@@ ...
 *  @....@ @@@@. .@@@. @@@@. @@@@@@@@ ...
 *  ----__ __--- -____ ----_ ___----_ ___
 *  7b df e0  etc.. all of the bits are packed together horizontally.
 *  the above has spaces in it, to make the example more easily read. 
 *  it would really appear in the disk as:
 *
 *  01111011110011101111011111111000
 *  10000110001100011000111000011000
 *  11111111110100001000111000011000
 *  10000110001100001000111000011000
 *  10000110001100011000111000011000
 *  10000111110011101111011111111000
 *  ----____----____----____----____
 *
 * Generally, this contains all of the data for the font, each character
 * consecutively, although ordering of the glyphs in this data block
 * is arbitrary.
 *
 *
 * The <F_CLOC> pointer points to arrays of 32bit longs.  The elements
 * of this array start with character <F_LOWCHAR>, and end at <F_HIGHCHAR>
 * Contained in these longs, in the upper 16 bits are the pointers into
 * the above glyph data for the start of each of the characters.  This is
 * a bit count from the "left" of the array.  The lowere 16 bits contains
 * the widths of the characters.  For the above example, you might see
 * the following:
 *
 *  <F_CLOC>['A'] = 0x00000006
 *  <F_CLOC>['B'] = 0x00060005
 *  <F_CLOC>['C'] = 0x000C0005
 *  <F_CLOC>['D'] = 0x00110005
 *  <F_CLOC>['?'] = 0x00160008
 *
 *
 * <F_CSPACE> points to a table of 16 bit words that are indexed like
 * <F_CLOC> data.  These words contain the number of pixels wide that
 * each character should take up.  It usually is equal to either the
 * width of the character or perhaps has an extra bit takced on for 
 * fixed kerning-like thing...  Basically, only this number of bits
 * of the glyph data should be drawn.  No idea what happens if this
 * value is less than the character width.  I'd say draw out F_CLOC's
 * width of pixels, then add space to increase space to the below 
 * value.
 *
 * <F_CSPACE>[ 'A' ] = 0x0006
 * <F_CSPACE>[ 'B' ] = 0x0005
 * <F_CSPACE>[ 'C' ] = 0x0005
 * <F_CSPACE>[ 'D' ] = 0x0005
 * <F_CSPACE>[ '?' ] = 0x0008
 *
 * 
 * <F_CKERN> points to a table of 16 bit words that are indexed like
 * <F_CLOC> data.  These words contain the number of pixels that should
 * be added on to the character when drawing it, before drawing the next
 * character.  Generally, this is either 1 or 0 in my experience.
 *
 * <F_CKERN>[ 'A' ] = 0x0001
 * <F_CKERN>[ 'B' ] = 0x0001
 * <F_CKERN>[ 'C' ] = 0x0001
 * <F_CKERN>[ 'D' ] = 0x0001
 * <F_CKERN>[ '?' ] = 0x0000
 *
 */



/* ************************************************************ */
/*  Colorfont notes from RKRM, and old header files. */
/*  - i haven't figured out how this fits into the file yet... -scott */

/* ctf_Flags */
#define C_COLORMASK	(0x0f)
#define C_COLORFONT	(0x01)	/* colormap shows designer's colors */
#define C_GREYFONT	(0x02)	/* color map shows low-high brightnesses */
#define C_ANTIALIAS	(0x04)	/* solid through saturated */o

/* color font colors struct:
	word 	reserved
	word	number of colors in following table
	word * 	pointer to 4bits per component xRGB
*/

/* color text font structure:
	struct	TextFont 
	word	flags		extended flags
	byte	depth		#bitplanes
	byte	fgpen color
	byte	low		low color
	byte	high		high color
	byte	plane pick
	byte	plane on/off
	struct color font colors *
	bitplane pointers
*/
