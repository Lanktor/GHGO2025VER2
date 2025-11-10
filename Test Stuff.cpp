#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT TEST_Render(PGAME_INFO GIptr)
{
	INT              I;
	SDL_FRect        Dest;
	extern SDL_FRect GameDice[];

	Dest.x = 100;
	Dest.y = 100;
	Dest.w = Dest.h = 128;

	for(I = 0; I < 6; I++, Dest.x += 140)
	{ 
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &GameDice[I], &Dest);
	}

	return(TRUE);
}