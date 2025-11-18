#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>



INT COMPUTER_Initiate(PGAME_INFO GIptr)
{
	PCOMP_PLAYER_INFO CPIptr;

	CPIptr = &GIptr->GI_ComputerPlayer;

	CPIptr->CPI_RipTidesRemaining = MAX_RIPTIDES;
	CPIptr->CPI_CurRoll = 0;
	CPIptr->CPI_MaxRolls = MAX_ROLLS;
	COMPUTER_ResetDiceTable(GIptr);
	COMPUTER_ResetScoreTable(GIptr);

	return(TRUE);
}

INT COMPUTER_ResetDiceTable(PGAME_INFO GIptr)
{
	INT               I, J;
	PCOMP_DICE_INFO   CDIptr;
	PCOMP_PLAYER_INFO CPIptr;

	CPIptr = &GIptr->GI_ComputerPlayer;

	for(I = 0; I < CPIptr->CPI_MaxRolls; I++)
	{
		CDIptr = CPIptr->CPI_DiceTable[I];
		for (J = 0; J < MAX_DICE; J++, CDIptr++)
		{
			CDIptr->CDI_CurIdent = DICE_NO_IDENT;
			CDIptr->CDI_SaveIdent = DICE_NO_IDENT;
			CDIptr->CDI_Flag = DICE_NO_FLAG;
		}
	}

	return(TRUE);
}

INT COMPUTER_ResetScoreTable(PGAME_INFO GIptr)
{
	INT               I, J;
	PCOMP_SCORE_INFO  CSIptr;
	PCOMP_PLAYER_INFO CPIptr;

	CPIptr = &GIptr->GI_ComputerPlayer;

	for (I = 0; I < GAMEBOARD_CONST_MAX_COLUMNS; I++)
	{
		CSIptr = CPIptr->CPI_ScoreTable[I];
		for (J = 0; J < GAMEBOARD_CONST_MAX_ROWS; J++, CSIptr++)
		{
			CSIptr->CSI_Score = 0;
			CSIptr->CSI_ScoredFlag = FALSE;
		}
		CSIptr->CSI_Score = -1; // Table Terminator
		CSIptr->CSI_ScoredFlag = -1; // Table Terminator
	}

	return(TRUE);
}

INT COMPUTER_TakeTurn(PGAME_INFO GIptr)
{
	INT               TypeFlag;
	PCOMP_PLAYER_INFO CPIptr;
	PCOMP_DICE_INFO   CDIptr;

	printf("COMPUTER_TakeTurn\n");

	COMPUTER_ResetDiceTable(GIptr);
	// Turn 1
	CPIptr = &GIptr->GI_ComputerPlayer;
	CDIptr = CPIptr->CPI_DiceTable[0];
	COMPUTER_RollTheDice(GIptr);
	if ((COMPUTER_VERIFY_MatchedCount(GIptr, CDIptr, 5)) == TRUE)
	{
		printf("Tidal Wave Found\n");
		if((COMPUTER_ScoreCell5ofaKind(GIptr)) == TRUE) return(TRUE);
	}
	if ((COMPUTER_VERIFY_MatchedCount(GIptr, CDIptr, 4)) == TRUE)
	{
		printf("High Tide Found\n");
		if((COMPUTER_ScoreCell4ofaKind(GIptr)) == TRUE) return(TRUE);
	}
	if ((COMPUTER_VERIFY_FullHouse(GIptr, CDIptr)) == TRUE)
	{
		if((COMPUTER_ScoreCellFullHouse(GIptr)) == TRUE) return(TRUE);
		printf("Full House Found\n");
	}
	if ((COMPUTER_VERIFY_TwoPair(GIptr, CDIptr, &TypeFlag)) == TRUE)
	{
		printf("Two Pair Found Type [%s]\n", (TypeFlag == VERIFY_TWO_PAIR_TWO_COUNT) ? "TWO COUNT" : "FOUR COUNT");
	}
	return(TRUE);
}

INT COMPUTER_RollTheDice(PGAME_INFO GIptr)
{
	INT               I;
	PCOMP_PLAYER_INFO CPIptr;
	PCOMP_DICE_INFO   CDIptr;

	CPIptr = &GIptr->GI_ComputerPlayer;
	CDIptr = CPIptr->CPI_DiceTable[CPIptr->CPI_CurRoll];

	printf("COMPUTER Roll %d -- ", CPIptr->CPI_CurRoll + 1);
	for (I = 0; I < MAX_DICE; I++, CDIptr++)
	{
		if (CDIptr->CDI_CurIdent == DICE_NO_IDENT)
		{
			CDIptr->CDI_CurIdent = UTIL_RandomIntRange(&GIptr->GI_RNGState, 0, 5);
			printf("[%d] ", CDIptr->CDI_CurIdent);

		}
	}

	printf("\n");
	return(TRUE);
}

INT COMPUTER_VERIFY_TwoPair(PGAME_INFO GIptr, PCOMP_DICE_INFO CDIptr, PINT TypeFlag)
{
	INT        I, Score, TwoCount, FourCount;
	INT        Count[6] = { 0 };

	for (I = 0; I < 5; I++, CDIptr++)
	{
		if (CDIptr->CDI_CurIdent == DICE_NO_IDENT) continue;
		Count[CDIptr->CDI_CurIdent]++;
	}

	TwoCount = FourCount = 0;
	for (I = 0; I < 6; I++)
	{
		if (Count[I] == 4)
		{
			FourCount++;
		}
		if (Count[I] == 2)
		{
			TwoCount++;
		}
		if (Count[I] == 3)
		{
			TwoCount++;
		}
	}

	if (TwoCount == 2)
	{
		*TypeFlag = VERIFY_TWO_PAIR_TWO_COUNT;
		return(TRUE);
	}

	if (FourCount == 1)
	{
		*TypeFlag = VERIFY_TWO_PAIR_FOUR_COUNT;
		return(TRUE);
	}

	return(FALSE);
}

INT COMPUTER_VERIFY_FullHouse(PGAME_INFO GIptr, PCOMP_DICE_INFO CDIptr)
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

INT COMPUTER_VERIFY_MatchedCount(PGAME_INFO GIptr, PCOMP_DICE_INFO CDIptr, INT MatchCount)
{
	INT        I, Score, CountFlag;
	INT        Count[6] = { 0 };

	for (I = 0; I < 5; I++, CDIptr++)
	{
		if (CDIptr->CDI_CurIdent == DICE_NO_IDENT) continue;
		Count[CDIptr->CDI_CurIdent]++;
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



INT COMPUTER_ScoreCell5ofaKind(PGAME_INFO GIptr)
{
	return(TRUE);
}

INT COMPUTER_ScoreCell4ofaKind(PGAME_INFO GIptr)
{
	return(TRUE);
}

INT COMPUTER_ScoreCellFullHouse(PGAME_INFO GIptr)
{
	return(TRUE);
}

INT COMPUTER_ScoreCellTwoPair(PGAME_INFO GIptr)
{
	return(TRUE);
}

INT COMPUTER_ScoreCellChance(PGAME_INFO GIptr)
{
	return(TRUE);
}

INT COMPUTER_ScoreCellDice(PGAME_INFO GIptr)
{
	return(TRUE);
}



