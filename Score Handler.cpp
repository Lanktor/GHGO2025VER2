#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT SCORE_ProcessUpper(PGAME_INFO GIptr)
{
	INT        I, Row, Col, Score;
	INT        Mask, LSFlag, SSFlag;
	PDICE_INFO DIptr;
	PROLL_INFO RIptr;
/*
	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];
	printf("Row [%d] Col [%d]\n", Row, Col);

	if (Row >= 1 && Row <= 6)
	{
		printf("Score Dice\n");
	}
*/
	SCORE_GetRowCol(GIptr, &Row, &Col);
	if(GIptr->GI_ScoreColumns[Col][Row].GBI_ScoredFlag == TRUE) return(FALSE);
	Score = 0;
	switch (Row)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			SCORE_DiceData(GIptr, Row, Col);
		break;

		// Ripples - Two Pair
		case 7:
			if((VERIFY_TwoPair(GIptr)) == TRUE)
			{
				Score = (SCORE_TWOPAIR * (Col + 1));
			}
			SCORE_Cell(GIptr, Row, Col, Score);
			break;

		// Seaweed - Chance 
		case 8:
			Score = (SCORE_CHANCE * (Col + 1));
			SCORE_Cell(GIptr, Row, Col, Score);
		break;

		// Breaker - Full House
		case 9:
			if((VERIFY_FullHouse(GIptr)) == TRUE)
			{
				Score = (SCORE_FULLHOUSE * (Col + 1));
			}
			SCORE_Cell(GIptr, Row, Col, Score);
			break;

		// High Tide 4 of a kind
		case 10:
			if ((VERIFY_MatchedCount(GIptr, 4)) == TRUE)
			{
				Score = (SCORE_FOUROFAKIND * (Col + 1));
			}
			SCORE_Cell(GIptr, Row, Col, Score);
			break;

		// Tidal Wave -- Yahtzee
		case 11:
			if ((VERIFY_MatchedCount(GIptr, 5)) == TRUE)
			{
				Score = (SCORE_FIVEOFAKIND * (Col + 1));
			}
			SCORE_Cell(GIptr, Row, Col, Score);
		break;

		default:
		break;
	}

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

INT SCORE_Cell(PGAME_INFO GIptr, INT Row, INT Col, INT Score)
{
	GIptr->GI_ScoreColumns[Col][Row].GBI_Score = Score;
	GIptr->GI_ScoreColumns[Col][Row].GBI_ScoredFlag = TRUE;
	GIptr->GI_CurrentScore += Score;
	sprintf_s((PCHAR)GIptr->GI_ScoreColumns[Col][Row].GBI_Text, 30, "%d", Score);
	DICE_InitiateTurn(GIptr);
	return(TRUE);
}

INT SCORE_DiceData(PGAME_INFO GIptr, INT Row, INT Col)
{
	INT        I, Score, IdentMatch;
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];
	IdentMatch = (Row - 1); // Row is 1 - 6;  Ident = 0 - 5
	Score = 0;

	for (I = 0; I < MAX_DICE; I++, DIptr++)
	{
		if(DIptr->DI_CurIdent == IdentMatch)
		{
			Score += 5;
		}
	}

	Score *= (Col + 1); // is 0 - 4 and Must add 1 to Col for Bonus Multiplier

	GIptr->GI_ScoreColumns[Col][Row].GBI_Score = Score;
	GIptr->GI_ScoreColumns[Col][Row].GBI_ScoredFlag = TRUE;
	GIptr->GI_CurrentScore += Score;
	sprintf_s((PCHAR)GIptr->GI_ScoreColumns[Col][Row].GBI_Text, 30, "%d", Score);
	DICE_InitiateTurn(GIptr);

	return(Score);
}

INT SCORE_FullHouse(PGAME_INFO GIptr, INT Row, INT Col)
{
	INT        I, Score, ThreeFlag, TwoFlag;
	INT        Count[6] = {0};
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;

	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];

	TwoFlag = ThreeFlag = 0;

	for (I = 0; I < 5; I++, DIptr++)
	{
		if(DIptr->DI_CurIdent == DICE_NO_IDENT) continue;
		Count[DIptr->DI_CurIdent]++;
	}

	for (I = 0; I < 6; I++)
	{
		if (Count[I] == 3) ThreeFlag = 1;
		if (Count[I] == 2) TwoFlag = 1;
	}

	if(ThreeFlag && TwoFlag)
	{
		Score = (SCORE_FULLHOUSE * (Col + 1));
		GIptr->GI_ScoreColumns[Col][Row].GBI_Score = Score;
		GIptr->GI_ScoreColumns[Col][Row].GBI_ScoredFlag = TRUE;
		GIptr->GI_CurrentScore += Score;
		sprintf_s((PCHAR)GIptr->GI_ScoreColumns[Col][Row].GBI_Text, 30, "%d", Score);
		DICE_InitiateTurn(GIptr);
	}
	return(Score);
}

INT SCORE_TwoPair(PGAME_INFO GIptr, INT Row, INT Col)
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
		if (Count[I] == 2) TwoCount++;
	}

	if (TwoCount == 2  || FourCount == 1)
	{
		Score = (SCORE_TWOPAIR * (Col + 1));
		GIptr->GI_ScoreColumns[Col][Row].GBI_Score = Score;
		GIptr->GI_ScoreColumns[Col][Row].GBI_ScoredFlag = TRUE;
		GIptr->GI_CurrentScore += Score;
		sprintf_s((PCHAR)GIptr->GI_ScoreColumns[Col][Row].GBI_Text, 30, "%d", Score);
		DICE_InitiateTurn(GIptr);
	}
	return(Score);
}

INT SCORE_Chance(PGAME_INFO GIptr, INT Row, INT Col)
{
	INT Score;

	Score = (SCORE_CHANCE * (Col + 1));
	GIptr->GI_ScoreColumns[Col][Row].GBI_Score = Score;
	GIptr->GI_ScoreColumns[Col][Row].GBI_ScoredFlag = TRUE;
	GIptr->GI_CurrentScore += Score;
	sprintf_s((PCHAR)GIptr->GI_ScoreColumns[Col][Row].GBI_Text, 30, "%d", Score);
	DICE_InitiateTurn(GIptr);

	return(Score);
}

INT SCORE_FourOfAKind(PGAME_INFO GIptr, INT Row, INT Col)
{
	INT        I, Score, FourCount;
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

	FourCount = 0;
	for (I = 0; I < 6; I++)
	{
		if (Count[I] == 4) FourCount++;
	}

	if (FourCount == 1)
	{
		Score = (SCORE_FOUROFAKIND * (Col + 1));
		GIptr->GI_ScoreColumns[Col][Row].GBI_Score = Score;
		GIptr->GI_ScoreColumns[Col][Row].GBI_ScoredFlag = TRUE;
		GIptr->GI_CurrentScore += Score;
		sprintf_s((PCHAR)GIptr->GI_ScoreColumns[Col][Row].GBI_Text, 30, "%d", Score);
		DICE_InitiateTurn(GIptr);
	}
	return(Score);
}

INT SCORE_FiveOfAKind(PGAME_INFO GIptr, INT Row, INT Col)
{
	INT        I, Score, FourCount;
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

	FourCount = 0;
	for (I = 0; I < 6; I++)
	{
		if (Count[I] == 5) FourCount++;
	}

	if (FourCount == 1)
	{
		Score = (SCORE_FIVEOFAKIND * (Col + 1));
		GIptr->GI_ScoreColumns[Col][Row].GBI_Score = Score;
		GIptr->GI_ScoreColumns[Col][Row].GBI_ScoredFlag = TRUE;
		GIptr->GI_CurrentScore += Score;
		sprintf_s((PCHAR)GIptr->GI_ScoreColumns[Col][Row].GBI_Text, 30, "%d", Score);
		DICE_InitiateTurn(GIptr);
	}
	return(Score);
}
























INT SCORE_Swells(PGAME_INFO GIptr, INT Row, INT Col, PINT SSFlag, PINT LSFlag)
{
	INT        I, Score, Mask;
	INT        Seen[6], Counter;
	PROLL_INFO RIptr;
	PDICE_INFO DIptr;

	Mask = 0;
	RIptr = &GIptr->GI_RollData;
	DIptr = RIptr->RI_DiceRolls[RIptr->RI_CurRoll];

	for(I = 0; I < 6; I++) Seen[I] = 0;
	for (I = 0; I < MAX_DICE; I++, DIptr++)
	{
		if(DIptr->DI_CurIdent == DICE_NO_IDENT) continue;
		Seen[DIptr->DI_CurIdent] = 1;
	}

	*SSFlag = FALSE;
	*LSFlag = FALSE;
	Counter = 0;
	for (I = 0; I < 6; I++) printf("%d ", Seen[I]);
	printf("\n");

	for (I = 0; I < 6; I++)
	{
		Mask |= (1 << I);
		if (Seen[I])
		{
			Counter++;
printf("Counter = [%d]\n", Counter);
			if (Counter == 5) *LSFlag = TRUE;
			if (Counter == 4) *SSFlag = TRUE;
		}
		else
		{
			Counter = 0;
		}
	}

	return(Mask);
}