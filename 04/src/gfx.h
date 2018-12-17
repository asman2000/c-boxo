#ifndef BOXO_GFX_H
#define BOXO_GFX_H
/*--------------------------------------------------------------------------*/

extern int GfxInit(void);
extern void GfxKill(void);

extern void GfxDrawTitle(void);

extern void GfxDrawTileEmpty(int x, int y);
extern void GfxDrawTileRock(int x, int y);
/*--------------------------------------------------------------------------*/
#endif // BOXO_GFX_H
