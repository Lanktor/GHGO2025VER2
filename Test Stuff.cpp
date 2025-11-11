#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT TEST_Render(PGAME_INFO GIptr)
{
	INT              I, J, Y;
	SDL_FRect        Dest, Rect;
	SDL_Color        Color = {8, 40, 40, 255};
	extern SDL_FRect GameDiceSrce[];
	extern SDL_Color GradientColor[];

	Rect.x = 445;
	Rect.y =  55;
	Rect.w = 980;
	Rect.h = 744;
	for (I = 0; I < 5; I++)
	{
		SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, GradientColor[I].r, GradientColor[I].g, GradientColor[I].b, GradientColor[I].a);
		for (J = 0; J < 3; J++)
		{
			SDL_RenderRect(GIptr->GI_MainRenderer, &Rect);
			Rect.x++;
			Rect.y++;
			Rect.w -= 2;
			Rect.h -= 2;
		}
	}

	Y = 880;
	Dest.x = 496;
	Dest.y = Y;
	Dest.w = Dest.h = 128;

	for(I = 0; I < 6; I++, Dest.x += 140)
	{ 
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &GameDiceSrce[I], &Dest);
	}


	return(TRUE);
}