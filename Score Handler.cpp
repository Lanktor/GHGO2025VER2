#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT SCORE_ProcessUpper(PGAME_INFO GIptr)
{
	INT Row, Col;

	SCORE_GetRowCol(GIptr, &Row, &Col);
	printf("Row [%d] Col [%d]\n", Row, Col);

	return(TRUE);
}

INT SCORE_GetRowCol(PGAME_INFO GIptr, PINT Row, PINT Col)
{
	INT             LocalRow, LocalCol;
	SDL_FRect       MouseRect;
	PROLL_INFO      RIptr;
	PDICE_INFO      DIptr;
	PGAMEBOARD_INFO GBIptr;

	MouseRect.x = GIptr->GI_MouseX;
	MouseRect.y = GIptr->GI_MouseY;
	MouseRect.w = 1;
	MouseRect.h = 1;

	for (LocalCol = 0; LocalCol < 5; LocalCol++)
	{
		GBIptr =GIptr->GI_ScoreColumns[LocalCol];
		for (LocalRow = 0; GBIptr->GBI_NormalSrce != NULL; GBIptr++, LocalRow++)
		{
			if ((SDL_HasRectIntersectionFloat(&MouseRect, &GBIptr->GBI_Dest)) == TRUE)
			{
				*Row = LocalRow;
				*Col = LocalCol;
				return(TRUE);
			}
		}
	}
	return(FALSE);
}