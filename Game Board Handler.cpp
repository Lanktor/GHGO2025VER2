#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>


INT GAMEBOARD_ProcessHover(PGAME_INFO GIptr)
{
	INT             I, J;
	PDICE_INFO      DIptr;
	PROLL_INFO      RIptr;
	PGAMEBOARD_INFO GBIptr;
	SDL_FRect       MouseRect;
	extern SDL_FRect BasicAreas[];

	MouseRect.x = GIptr->GI_MouseX;
	MouseRect.y = GIptr->GI_MouseY;
	MouseRect.w = 1;
	MouseRect.h = 1;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];

	for (I = 0, GBIptr = GIptr->GI_ScoreCategory; GBIptr->GBI_NormalSrce != NULL; GBIptr++, I++) GBIptr->GBI_Flag = GAMEBOARD_FLAG_HOVER_OFF;
	for (I = 0; I < 5; I++)
	{
		GBIptr = GIptr->GI_ScoreColumns[I];
		for (J = 0; GBIptr->GBI_NormalSrce != NULL; GBIptr++, J++) GBIptr->GBI_Flag = GAMEBOARD_FLAG_HOVER_OFF;
	}

	for (I = 0; I < MAX_DICE; I++, DIptr++) DIptr->DI_HoverFlag = GAMEBOARD_FLAG_HOVER_OFF;

	for (I = 0, GBIptr = GIptr->GI_ScoreCategory; GBIptr->GBI_NormalSrce != NULL; GBIptr++, I++)
	{
		if ((SDL_HasRectIntersectionFloat(&MouseRect, &GBIptr->GBI_Dest)) == TRUE)
		{
			GBIptr->GBI_Flag = GAMEBOARD_FLAG_HOVER_ON;
			return(TRUE);
		}
	}

	for (I = 0; I < 5; I++)
	{
		GBIptr = GIptr->GI_ScoreColumns[I];
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
	INT             I, TextXCenter, RowCounter;
	PGAMEBOARD_INFO GBIptr;
	SDL_FRect       TextDest, IconDest;
	PSDL_FRect      Srceptr, DiceSrceptr;
	SDL_Color       Color = { 8, 40, 40, 255 };
	PROLL_INFO      RIptr;
	PDICE_INFO      DIptr;

	RIptr = &GIptr->GI_RollData;
	DiceSrceptr = RIptr->RI_DiceSrce;

	for (RowCounter = 0, GBIptr = GIptr->GI_ScoreCategory; GBIptr->GBI_NormalSrce != NULL; GBIptr++, RowCounter++)
	{
		Srceptr = (GBIptr->GBI_Flag == GAMEBOARD_FLAG_HOVER_OFF) ? GBIptr->GBI_NormalSrce : GBIptr->GBI_HiliteSrce;

		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_GameBoardTexture, Srceptr, &GBIptr->GBI_Dest);

		if((RowCounter >= 1) && (RowCounter <= 6))
		{
			IconDest.x = GBIptr->GBI_Dest.x + GBIptr->GBI_Dest.w - 60;
			IconDest.y = GBIptr->GBI_Dest.y + 8;
			IconDest.w = IconDest.h = 48;
			SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, DiceSrceptr, &IconDest);
			DiceSrceptr++;
		}

		TextDest.x = GBIptr->GBI_Dest.x + GBIptr->GBI_TextOffsetX;
		TextDest.y = GBIptr->GBI_Dest.y + GBIptr->GBI_TextOffsetY;
		TEXT_WriteText(GIptr, Color, &TextDest, GBIptr->GBI_Text, 1);
	}

	for(I = 0; I < GAMEBOARD_CONST_MAX_COLUMNS; I++)
	{
		GBIptr = GIptr->GI_ScoreColumns[I];

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
	Rect.w = 731;
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
			SCORE_ProcessUpper(GIptr);
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