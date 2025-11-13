#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

SDL_FRect DisplayScoreTable[] =
{
	{  0, 330, 312, 322 }, // Blank
	{640, 750,  60,  60 }, // Dark Button Icon
};


INT TEST_Render(PGAME_INFO GIptr)
{
	CHAR       Text[1024];
	INT        I, J, Y;
	SDL_FRect  Dest, Rect;
	SDL_Color  Color = {8, 40, 40, 255};
	PROLL_INFO RIptr;

	RIptr = &GIptr->GI_RollData;

	GIptr->GI_CurrentScore++;

	// Score Display
	Dest.x = 1520;
	Dest.y = 300;
	Dest.w = 320;
	Dest.h = 300;
	SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &DisplayScoreTable[0], &Dest);

	Dest.x = 1560;
	Dest.y =  450;
	Dest.w =  240;
	Dest.h =  120;
	SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &DisplayScoreTable[0], &Dest);


	sprintf_s(Text, sizeof(Text), "Score");
	Dest.x = TEXT_CalculateCenterText(GIptr, Text, 2, 320);
	Dest.x += 1520;
	Dest.y = 350;
	TEXT_WriteText(GIptr, Color, &Dest, Text, 2);

	sprintf_s(Text, sizeof(Text), "%04d", GIptr->GI_CurrentScore);
	Dest.x = TEXT_CalculateCenterText(GIptr, Text, 2, 240);
	Dest.x += 1560;
	Dest.y = 485;
	TEXT_WriteText(GIptr, Color, &Dest, Text, 2);

	// Current Roll Display

	Dest.x = 1560;
	Dest.y = 900;
	Dest.w = 60;
	Dest.h = 60;
	SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &DisplayScoreTable[1], &Dest);
	sprintf_s(Text, sizeof(Text), "%d", RIptr->RI_CurRoll + 1);
	Dest.x = TEXT_CalculateCenterText(GIptr, Text, 2, 60);
	Dest.x += 1560;
	Dest.y += 5;
	TEXT_WriteText(GIptr, Color, &Dest, Text, 2);

	// Current Rip Tides Display
	Dest.x = 1560;
	Dest.y = 970;
	SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &DisplayScoreTable[1], &Dest);
	sprintf_s(Text, sizeof(Text), "%d", RIptr->RI_RipTidesRemaining);
	Dest.x = TEXT_CalculateCenterText(GIptr, Text, 2, 60);
	Dest.x += 1560;
	Dest.y += 5;
	TEXT_WriteText(GIptr, Color, &Dest, Text, 2);

	return(TRUE);
}