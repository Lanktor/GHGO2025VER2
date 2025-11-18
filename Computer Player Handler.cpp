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
	printf("COMPUTER_TakeTurn\n");

	// Turn 1
	COMPUTER_RollTheDice(GIptr);
	return(TRUE);
}

INT COMPUTER_RollTheDice(PGAME_INFO GIptr)
{
	INT               I;
	PCOMP_PLAYER_INFO CPIptr;
	PCOMP_DICE_INFO   CDIptr;

	CPIptr = &GIptr->GI_ComputerPlayer;
	CDIptr = CPIptr->CPI_DiceTable[CPIptr->CPI_CurRoll];

	printf("COMPUTER Roll [%d] ", CPIptr->CPI_CurRoll + 1);
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