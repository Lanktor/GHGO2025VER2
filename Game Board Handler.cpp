#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

SDL_FRect BoxSrce[] = 
{
	{ 0,  0,  300,  64}, // Normal Header
	{ 0, 80,  300,  64}, // Hilite Header
	{310,  0, 120,  64}, // Normal Score Column
	{310, 80, 120,  64}, // Hilite Score Column
};

GAMEBOARD_INFO Header[] =
{
	{&BoxSrce[0], &BoxSrce[1], 490,  71, 300, 64,    10, 20,    "Category",    0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 130, 300, 64,    10, 20,    "Waves ",       0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 189, 300, 64,    10, 20,    "Shells",      0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 248, 300, 64,    10, 20,    "Fishes",      0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 307, 300, 64,    10, 20,    "Anchor",      0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 366, 300, 64,    10, 20,    "Whales",      0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 425, 300, 64,    10, 20,    "Pools",       0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 484, 300, 64,    10, 20,    "Small Swell 30", 0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 543, 300, 64,    10, 20,    "Large Swell 40", 0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 602, 300, 64,    10, 20,    "Breaker 40",     0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 661, 300, 64,    10, 20,    "High Tide 40",   0, 0},
	{&BoxSrce[0], &BoxSrce[1], 490, 720, 300, 64,    10, 20,    "Tidal Wave 100",  0, 0},
	{ NULL},
};

GAMEBOARD_INFO ScoreColumn1[] =
{
	{&BoxSrce[2], &BoxSrce[3], 800,  71, 120, 64,    50, 20,    "1x", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 130, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 189, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 248, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 307, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 366, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 425, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 484, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 543, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 602, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 661, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 800, 720, 120, 64,    10, 20,    "", 0, 0},
	{ NULL},
};

GAMEBOARD_INFO ScoreColumn2[] =
{
	{&BoxSrce[2], &BoxSrce[3], 930,  71, 120, 64,    44, 20,    "2x", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 130, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 189, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 248, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 307, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 366, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 425, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 484, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 543, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 602, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 661, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 930, 720, 120, 64,    10, 20,    "", 0, 0},
	{NULL},
};

GAMEBOARD_INFO ScoreColumn3[] =
{
	{&BoxSrce[2], &BoxSrce[3], 1060,  71, 120, 64,    43, 20,    "3x", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 130, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 189, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 248, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 307, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 366, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 425, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 484, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 543, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 602, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 661, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1060, 720, 120, 64,    10, 20,    "", 0, 0},
	{NULL},
};

GAMEBOARD_INFO ScoreColumn4[] =
{
	{&BoxSrce[2], &BoxSrce[3], 1190,  71, 120, 64,    43, 20,    "4x", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 130, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 189, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 248, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 307, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 366, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 425, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 484, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 543, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 602, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 661, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1190, 720, 120, 64,    10, 20,    "", 0, 0},
	{NULL},
};

GAMEBOARD_INFO ScoreColumn5[] =
{
	{&BoxSrce[2], &BoxSrce[3], 1320,  71, 120, 64,    43, 20,    "5x", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 130, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 189, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 248, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 307, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 366, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 425, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 484, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 543, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 602, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 661, 120, 64,    10, 20,    "", 0, 0},
	{&BoxSrce[2], &BoxSrce[3], 1320, 720, 120, 64,    10, 20,    "", 0, 0},
	{NULL},
};

INT GAMEBOARD_ProcessHover(PGAME_INFO GIptr)
{
	INT             I, J;
	PDICE_INFO      DIptr;
	PROLL_INFO      RIptr;
	PGAMEBOARD_INFO GBIptr;
	PGAMEBOARD_INFO GBIColPtrs[5];
	SDL_FRect       MouseRect;
	extern SDL_FRect BasicAreas[];

	MouseRect.x = GIptr->GI_MouseX;
	MouseRect.y = GIptr->GI_MouseY;
	MouseRect.w = 1;
	MouseRect.h = 1;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];

	GBIColPtrs[0] = ScoreColumn1;
	GBIColPtrs[1] = ScoreColumn2;
	GBIColPtrs[2] = ScoreColumn3;
	GBIColPtrs[3] = ScoreColumn4;
	GBIColPtrs[4] = ScoreColumn5;
	for (I = 0, GBIptr = Header; GBIptr->GBI_NormalSrce != NULL; GBIptr++, I++) GBIptr->GBI_Flag = GAMEBOARD_FLAG_HOVER_OFF;
	for (I = 0; I < 5; I++)
	{
		GBIptr = GBIColPtrs[I];
		for (J = 0; GBIptr->GBI_NormalSrce != NULL; GBIptr++, J++) GBIptr->GBI_Flag = GAMEBOARD_FLAG_HOVER_OFF;
	}

	for (I = 0; I < MAX_DICE; I++, DIptr++) DIptr->DI_HoverFlag = GAMEBOARD_FLAG_HOVER_OFF;

	for (I = 0, GBIptr = Header; GBIptr->GBI_NormalSrce != NULL; GBIptr++, I++)
	{
		if ((SDL_HasRectIntersectionFloat(&MouseRect, &GBIptr->GBI_Dest)) == TRUE)
		{
			GBIptr->GBI_Flag = GAMEBOARD_FLAG_HOVER_ON;
			return(TRUE);
		}
	}

	for (I = 0; I < 5; I++)
	{
		GBIptr = GBIColPtrs[I];
		for (J = 0; GBIptr->GBI_NormalSrce != NULL; GBIptr++, J++)
		{
			if ((SDL_HasRectIntersectionFloat(&MouseRect, &GBIptr->GBI_Dest)) == TRUE)
			{
				GBIptr->GBI_Flag = GAMEBOARD_FLAG_HOVER_ON;
				return(TRUE);
			}
		}
	}

	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];
	for (I = 0; I < MAX_DICE; I++, DIptr++)
	{
		if ((SDL_HasRectIntersectionFloat(&MouseRect, &DIptr->DI_Pos)) == TRUE)
		{
			DIptr->DI_HoverFlag = GAMEBOARD_FLAG_HOVER_ON;
			return(TRUE);
		}

	}
	return(TRUE);
}

INT GAMEBOARD_Render(PGAME_INFO GIptr)
{
	CHAR            BonusText[20];
	INT             I, TextXCenter;
	PGAMEBOARD_INFO GBIptr;
	PGAMEBOARD_INFO GBIColPtrs[5];
	SDL_FRect       TextDest;
	PSDL_FRect      Srceptr;
	SDL_Color       Color = { 8, 40, 40, 255 };

	GBIColPtrs[0] = ScoreColumn1;
	GBIColPtrs[1] = ScoreColumn2;
	GBIColPtrs[2] = ScoreColumn3;
	GBIColPtrs[3] = ScoreColumn4;
	GBIColPtrs[4] = ScoreColumn5;
	for (GBIptr = Header; GBIptr->GBI_NormalSrce != NULL; GBIptr++)
	{
		Srceptr = (GBIptr->GBI_Flag == GAMEBOARD_FLAG_HOVER_OFF) ? GBIptr->GBI_NormalSrce : GBIptr->GBI_HiliteSrce;

		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_GameBoardTexture, Srceptr, &GBIptr->GBI_Dest);
		TextDest.x = GBIptr->GBI_Dest.x + GBIptr->GBI_TextOffsetX;
		TextDest.y = GBIptr->GBI_Dest.y + GBIptr->GBI_TextOffsetY;
		TEXT_WriteText(GIptr, Color, &TextDest, GBIptr->GBI_Text, 1);
	}

	for(I = 0; I < 5; I++)
	{
		GBIptr = GBIColPtrs[I];

		for (; GBIptr->GBI_NormalSrce != NULL; GBIptr++)
		{
			Srceptr = (GBIptr->GBI_Flag == GAMEBOARD_FLAG_HOVER_OFF) ? GBIptr->GBI_NormalSrce : GBIptr->GBI_HiliteSrce;

			SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_GameBoardTexture, Srceptr, &GBIptr->GBI_Dest);
			TextDest.x = GBIptr->GBI_Dest.x + GBIptr->GBI_TextOffsetX;
			TextDest.y = GBIptr->GBI_Dest.y + GBIptr->GBI_TextOffsetY;
			TEXT_WriteText(GIptr, Color, &TextDest, GBIptr->GBI_Text, 1);
		}
	}

	GAMEBOARD_RenderBorder(GIptr);
	return(TRUE);
}

INT GAMEBOARD_RenderBorder(PGAME_INFO GIptr)
{
	INT              I, J, Y;
	SDL_FRect        Dest, Rect;
	SDL_Color        Color = { 8, 40, 40, 255 };
	extern SDL_FRect GameDiceSrce[];
	extern SDL_Color GradientColor[];

	Rect.x = 475;
	Rect.y = 55;
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

	Rect.x = 590;
	Rect.y = 860;
	Rect.w = 735;
	Rect.h = 170;
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
	return(TRUE);
}

INT GAMEBOARD_ProcessMouseClick(PGAME_INFO GIptr)
{
	INT              Func;
	SDL_FRect        MouseRect;
	PSDL_FRect       Ptr;
	extern SDL_FRect BasicAreas[];

	MouseRect.x = GIptr->GI_MouseX;
	MouseRect.y = GIptr->GI_MouseY;
	MouseRect.w = 1;
	MouseRect.h = 1;

	Ptr = BasicAreas;
	for (Func = 0; Ptr->x != -1; Ptr++, Func++)
	{
		if ((SDL_HasRectIntersectionFloat(&MouseRect, Ptr)) == TRUE)
		{
			break;
		}
	}

	if(Ptr->x == -1) return(FALSE);

	switch (Func)
	{
		case 0:
			printf("Upper Process\n");
		break;

		case 1:
			printf("Dice Process\n");
			DICE_ProcessPick(GIptr, &MouseRect);
		break;

		default:
		break;
	}
	return(TRUE);
}