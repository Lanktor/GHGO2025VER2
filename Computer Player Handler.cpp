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

	CPIptr->CPI_RipTidesRemaining = 3;
	return(TRUE);
}

INT COMPUTER_TakeTurn(PGAME_INFO GItpr)
{
	return(TRUE);
}