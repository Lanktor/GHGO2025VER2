#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>


INT DICE_Render(PGAME_INFO GIptr)
{
	INT        I;
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;
	PSDL_FRect Srceptr;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];

	for (I = 0; I < MAX_DICE; I++, DIptr++)
	{
		if (DIptr->DI_CurIdent == DICE_NO_IDENT)
		{
			Srceptr = (DIptr->DI_HoverFlag == GAMEBOARD_FLAG_HOVER_ON) ? RIptr->RI_DiceSrceHover : RIptr->RI_DiceSrce;
			SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &Srceptr[6], &DIptr->DI_Pos);
		}
		else
		{
			Srceptr = (DIptr->DI_HoverFlag == GAMEBOARD_FLAG_HOVER_ON) ? RIptr->RI_DiceSrceHover : RIptr->RI_DiceSrce;
			SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &Srceptr[DIptr->DI_CurIdent], &DIptr->DI_Pos);
		}
	}

	return(TRUE);
}

INT DICE_Roll(PGAME_INFO GIptr, PDICE_INFO DIptr)
{
	INT I;
	for (I = 0; I < MAX_DICE; I++, DIptr++)
	{
		if(DIptr->DI_CurIdent = DICE_NO_IDENT)
		{
			DIptr->DI_CurIdent = UTIL_RandomIntRange(&GIptr->GI_RNGState, 0, 5);
		}
	}
	return(TRUE);
}

INT DICE_Initiate(PGAME_INFO GIptr)
{
	INT        I, J;
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;
	SDL_FRect  Dest;
	extern SDL_FRect GameDiceSrce[];
	extern SDL_FRect GameDiceHover[];

	RIptr = &GIptr->GI_RollData;

	RIptr->RI_CurRoll = 0;
	RIptr->RI_Flag = 0;

	RIptr->RI_DiceSrce = GameDiceSrce;
	RIptr->RI_DiceSrceHover = GameDiceHover;

	for(I = 0; I < 3; I++)
	{
		Dest.x = 610;
		Dest.y = 880;
		Dest.w = Dest.h = 128;

		DIptr = RIptr->RI_DiceRolls[I];
		DICE_Clear(GIptr, DIptr);
		for(J = 0; J < MAX_DICE; J++, DIptr++, Dest.x += 140)
		{
			DIptr->DI_HoverFlag = GAMEBOARD_FLAG_HOVER_OFF;
			DIptr->DI_Flag = DICE_NO_FLAG;
			DIptr->DI_Pos.x = Dest.x;
			DIptr->DI_Pos.y = Dest.y;
			DIptr->DI_Pos.w = Dest.w;
			DIptr->DI_Pos.h = Dest.h;
		}
	}
	return(TRUE);
}

INT DICE_Clear(PGAME_INFO GIptr, PDICE_INFO DIptr)
{
	INT I;

	for(I = 0; I < 5; I++)
	{
		DIptr->DI_Flag = DICE_NO_FLAG;
		DIptr->DI_SaveIdent = DICE_NO_IDENT;
		DIptr->DI_CurIdent = DICE_NO_IDENT;
	}
	return(TRUE);
}

INT DICE_ProcessPick(PGAME_INFO GIptr, PSDL_FRect Mptr)
{
	INT        Die;
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];

	for (Die = 0; Die < MAX_DICE; Die++, DIptr++)
	{
		if ((SDL_HasRectIntersectionFloat(Mptr, &DIptr->DI_Pos)) == TRUE)
		{
			break;
		}
	}

	if(Die == MAX_DICE) return(FALSE);

printf("DIE = [%d]\n", Die);
	return(TRUE);
}