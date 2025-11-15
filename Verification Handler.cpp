#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT VERIFY_TwoPair(PGAME_INFO GIptr)
{
	INT        I, Score, TwoCount, FourCount;
	INT        Count[6] = { 0 };
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];

	for (I = 0; I < 5; I++, DIptr++)
	{
		if (DIptr->DI_CurIdent == DICE_NO_IDENT) continue;
		Count[DIptr->DI_CurIdent]++;
	}

	TwoCount = FourCount = 0;
	for (I = 0; I < 6; I++)
	{
		if (Count[I] == 4) FourCount++;
		if ((Count[I] == 2) || Count[I] == 3) TwoCount++;
	}

	if (TwoCount == 2 || FourCount == 1)
	{
		return(TRUE);
	}

	return(FALSE);
}

INT VERIFY_FullHouse(PGAME_INFO GIptr)
{
	INT        I, Score, ThreeFlag, TwoFlag;
	INT        Count[6] = { 0 };
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];

	TwoFlag = ThreeFlag = 0;

	for (I = 0; I < 5; I++, DIptr++)
	{
		if (DIptr->DI_CurIdent == DICE_NO_IDENT) continue;
		Count[DIptr->DI_CurIdent]++;
	}

	for (I = 0; I < 6; I++)
	{
		if (Count[I] == 3) ThreeFlag = 1;
		if (Count[I] == 2) TwoFlag = 1;
	}

	if (ThreeFlag && TwoFlag)
	{
		return(TRUE);
	}
	return(FALSE);
}

INT VERIFY_MatchedCount(PGAME_INFO GIptr, INT MatchCount)
{
	INT        I, Score, CountFlag;
	INT        Count[6] = { 0 };
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];


	for (I = 0; I < 5; I++, DIptr++)
	{
		if (DIptr->DI_CurIdent == DICE_NO_IDENT) continue;
		Count[DIptr->DI_CurIdent]++;
	}

	CountFlag = 0;
	for (I = 0; I < 6; I++)
	{
		if (Count[I] == MatchCount) CountFlag++;
	}

	if (CountFlag == 1)
	{
		return(TRUE);
	}
	return(FALSE);
}

