#include "gfx.h"
#include "window.h"


#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/datatypes.h>
#include <datatypes/pictureclass.h> 
/*--------------------------------------------------------------------------*/

static struct BitMap* bitmapTiles = NULL;

struct RastPort* rastPortTiles = NULL;
struct RastPort rastport;

struct RastPort* rastPortWindow = NULL;

static int GfxGetBitmapTiles(Object* o);
/*--------------------------------------------------------------------------*/

int GfxInit(void)
{
	int result = -1;
	
	rastPortWindow = WindowGetRastPort();

	struct Screen* screen = LockPubScreen(NULL);

	Object* o = NewDTObject("tiles.iff", DTA_GroupID, GID_PICTURE,
		PDTA_Remap, TRUE, PDTA_Screen, screen, TAG_END);

	if (NULL != o)
	{
		DoDTMethod(o, NULL, NULL, DTM_PROCLAYOUT,NULL,TRUE);
		
		result = GfxGetBitmapTiles(o);

		DisposeDTObject(o);
	}

	UnlockPubScreen(NULL, screen);

	return result;
}

/*--------------------------------------------------------------------------*/

static int GfxGetBitmapTiles(Object* o)
{
	struct BitMap* bm;
	GetDTAttrs(o, PDTA_DestBitMap, &bm, TAG_END);

	const ULONG width = GetBitMapAttr(bm, BMA_WIDTH);
	const ULONG height = GetBitMapAttr(bm, BMA_HEIGHT);
	const ULONG depth = GetBitMapAttr(bm, BMA_DEPTH);
	const ULONG flags = BMF_DISPLAYABLE|BMF_CLEAR;

	bitmapTiles = AllocBitMap(width, height, depth, flags, NULL);

	if (NULL != bitmapTiles)
	{
		BltBitMap(bm, 0, 0, bitmapTiles, 0, 0, width, height,
			0xC0, 0xFF, NULL);

		rastPortTiles = &rastport;
		InitRastPort(rastPortTiles);
		rastPortTiles->BitMap = bitmapTiles;

		return 0;
	}
	
	return -1;
}

/*--------------------------------------------------------------------------*/

void GfxKill(void)
{
	FreeBitMap(bitmapTiles);
}

/*--------------------------------------------------------------------------*/
void GfxDrawTitle(void)
{
	BltBitMapRastPort(bitmapTiles, 0, 16, rastPortWindow, 96, 24, 128, 32, 0xC0);

}
/*--------------------------------------------------------------------------*/
