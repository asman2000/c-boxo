#include "libs.h"

#include "types.h"

#include <proto/exec.h>

/*--------------------------------------------------------------------------*/

struct IntuitionBase* IntuitionBase = NULL;
struct GfxBase* GfxBase = NULL;
struct Library* UtilityBase = NULL;
struct Library* DataTypesBase = NULL;

/*--------------------------------------------------------------------------*/

int LibsOpen(void)
{
	IntuitionBase = (struct IntuitionBase*)
		OpenLibrary("intuition.library", 34);

	if (NULL == IntuitionBase)
	{
		return RT_FAILED_OPEN_INTUITION;
	}

	GfxBase = (struct GfxBase*)OpenLibrary("graphics.library", 34);

	if (NULL == GfxBase)
	{
		return RT_FAILED_OPEN_GRAPHICS;
	}

	UtilityBase = OpenLibrary("utility.library", 0);

	if (NULL == UtilityBase)
	{
		return RT_FAILED_OPEN_UTILITY;
	}

	DataTypesBase = OpenLibrary("datatypes.library",0);

	if (NULL == DataTypesBase)
	{
		return RT_FAILED_OPEN_DATATYPES;
	}
	
	return RT_OK;
}
/*--------------------------------------------------------------------------*/

void LibsClose(void)
{
	CloseLibrary(DataTypesBase);
	CloseLibrary(UtilityBase);
	CloseLibrary((struct Library*)IntuitionBase);
	CloseLibrary((struct Library*)GfxBase);
}

/*--------------------------------------------------------------------------*/
