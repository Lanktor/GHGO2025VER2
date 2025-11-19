#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT HISCORE_DisplayData(PGAME_INFO GIptr);
INT HIGHSCORE_Read(PGAME_INFO GIptr);
INT HIGHSCORE_Write(PGAME_INFO GIptr);

PHI_SCORE_DATA ReadBuffer;
INT            HiScoreRecords;

INT HighScoreHandler(PGAME_INFO GIptr)
{
	const  BOOL *KeyState;
	char         Text[1024];
	INT                Quit, Keys;
	INT                ButtonIdent;
	INT                ViewHiScoreFlag;
	SDL_Event          Event;
	SDL_FRect          Srce, Dest, TextDest, HiScoreDest;
	PPLAYER_INFO       PIptr;
	extern BUTTON_INFO HighScoreButtons[];
	extern SDL_FRect   HiScoreBox[];

	PIptr = &GIptr->GI_Player;

	GIptr->GI_TARGET_FPS = 80;
	GIptr->GI_FRAME_DELAY = 1000 / GIptr->GI_TARGET_FPS;

	GIptr->GI_SecondsCounter = GIptr->GI_PrevTime = SDL_GetTicks();
	GIptr->GI_FrameCounter = 0;
	KeyState = SDL_GetKeyboardState(NULL);

	if ((HIGHSCORE_Read(GIptr)) == FALSE)
	{
		EndOfGameHandler(GIptr);
	}

	for (Quit = FALSE; Quit != TRUE; GIptr->GI_FrameCounter++)
	{
		GIptr->GI_FrameStart = SDL_GetTicks();

		SDL_PumpEvents();

		while (SDL_PollEvent(&Event))
		{
			switch (Event.type)
			{

				case SDL_EVENT_KEY_DOWN:
					if (Event.key.scancode == SDL_SCANCODE_ESCAPE)
					{
						Quit = TRUE;
					}
				break;

				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					if (Event.button.button == SDL_BUTTON_LEFT)
					{
						ButtonIdent = BUTTON_ProcessClick(GIptr, HighScoreButtons);
						if (ButtonIdent == BUTTON_IDENT_EXIT) EndOfGameHandler(GIptr);
						if (ButtonIdent == BUTTON_IDENT_PLAY)
						{
							START_CreateNewGame(GIptr);
							Quit = TRUE;
						}
					}
					if (Event.button.button == SDL_BUTTON_RIGHT)
					{
					}
				break;

				case SDL_EVENT_MOUSE_BUTTON_UP:
					if (Event.button.button == SDL_BUTTON_LEFT)
					{
					}
				break;

			}
		}

		GIptr->GI_MouseState = SDL_GetMouseState(&GIptr->GI_MouseX, &GIptr->GI_MouseY);

		GIptr->GI_CurTime = SDL_GetTicks();
		GIptr->GI_DeltaTime = (GIptr->GI_CurTime - GIptr->GI_PrevTime) / 1000.0f;
		GIptr->GI_PrevTime = GIptr->GI_CurTime;

		SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, 0x00, 0x13, 0x63, 0x00);
		SDL_RenderClear(GIptr->GI_MainRenderer);
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_BackgroundTexture, NULL, NULL);
		BUTTON_Update(GIptr, HighScoreButtons, 212, 424);
		BUTTON_IsButtonHover(GIptr, HighScoreButtons);

		HISCORE_DisplayData(GIptr);

		SDL_RenderPresent(GIptr->GI_MainRenderer);

		GIptr->GI_FrameTime = SDL_GetTicks() - GIptr->GI_FrameStart;
		if (GIptr->GI_FrameTime < GIptr->GI_FRAME_DELAY) SDL_Delay(GIptr->GI_FRAME_DELAY - GIptr->GI_FrameTime);

		if (SDL_GetTicks() >= GIptr->GI_SecondsCounter + 1000)
		{
			printf("HighScoreHandler: FPS: [%d]\n", GIptr->GI_FrameCounter);
			GIptr->GI_FrameCounter = 0;
			GIptr->GI_SecondsCounter = SDL_GetTicks();
		}
	}
	return(TRUE);
}

INT CompareScores(const void *a, const void *b);


INT CompareScores(const void *a, const void *b)
{
	return(((PHI_SCORE_DATA)b)->HSD_Score - ((PHI_SCORE_DATA)a)->HSD_Score);
}

INT HIGHSCORE_Read(PGAME_INFO GIptr)
{
	INT            I;
	HI_SCORE_DATA  HSDData;
	INT            ErrorNum;
	INT            FileSize;
	PFILE          FP;

	if ((fopen_s(&FP, HI_SCORE_FILE, "rb+")) != 0)
	{
		if ((ErrorNum = fopen_s(&FP, HI_SCORE_FILE, "wb+")) != 0)
		{
			printf("No High Score File Error [%d]\n", ErrorNum);
			return(FALSE);
		}
	}

	fseek(FP, 0, SEEK_END);
	FileSize = ftell(FP);
	fseek(FP, 0, SEEK_SET);
	HiScoreRecords = (FileSize / SZ_HI_SCORE_DATA);
	ReadBuffer = (PHI_SCORE_DATA)SDL_calloc((HiScoreRecords + 1), SZ_HI_SCORE_DATA);
	printf("FileSize = [%d] Records [%d]\n", FileSize, HiScoreRecords);

	if ((fread(ReadBuffer, SZ_HI_SCORE_DATA, HiScoreRecords, FP)) != HiScoreRecords)
	{
		printf("Could not read file for [%d] bytes [%d] Records\n", FileSize, HiScoreRecords);
		fclose(FP);
		return(FALSE);
	}


	sprintf_s(HSDData.HSD_Name, MAX_NAME_LENGTH, "%s", GIptr->GI_PlayerName);
	HSDData.HSD_Score = GIptr->GI_CurrentScore;
	memcpy(&ReadBuffer[HiScoreRecords], &HSDData, SZ_HI_SCORE_DATA);

	HiScoreRecords++;
	printf("Writing HiScoreRecords [%d]\n", HiScoreRecords);
	fseek(FP, 0, SEEK_SET);
	fwrite(ReadBuffer, SZ_HI_SCORE_DATA, HiScoreRecords, FP);
	fclose(FP);

	for (I = 0; I < HiScoreRecords; I++)
	{
		printf("Name: [%s] Score [%d]\n", ReadBuffer[I].HSD_Name, ReadBuffer[I].HSD_Score);
	}

	printf("============================================================================================================\n");

	qsort(ReadBuffer, HiScoreRecords, SZ_HI_SCORE_DATA, CompareScores);

	for (I = 0; I < HiScoreRecords; I++)
	{
		printf("Name: [%s] Score [%d]\n", ReadBuffer[I].HSD_Name, ReadBuffer[I].HSD_Score);
	}
	return(TRUE);
}

INT HIGHSCORE_Write(PGAME_INFO GIptr)
{
	return(TRUE);
}

INT HISCORE_DisplayData(PGAME_INFO GIptr)
{
	CHAR             Text[100];
	INT              I, J, Yinc;
	FLOAT            Scale;
	SDL_FRect        Dest, Rect;
	SDL_Color        Color = { 8, 40, 40, 255 };
	extern SDL_FRect GameDiceSrce[];
	extern SDL_Color GradientColor[];

	Rect.x = 675;
	Rect.y = 200;
	Rect.w = 600;
	Rect.h = 500;
	SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, GradientColor[4].r, GradientColor[4].g, GradientColor[4].b, GradientColor[4].a);
	SDL_RenderFillRect(GIptr->GI_MainRenderer, &Rect);
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

	Rect.y = 230;
	for (I = 0; I < HiScoreRecords; I++)
	{
		if(I >= 10) break;
		Scale = (I == 0) ? 1.3 : 1;

		Rect.x = 750;
		sprintf_s(Text, sizeof(Text), "%d %s", (I + 1), ReadBuffer[I].HSD_Name);
		TEXT_WriteText(GIptr, GradientColor[0], &Rect, Text, Scale);
		sprintf_s(Text, sizeof(Text), "%d", ReadBuffer[I].HSD_Score);
		Rect.x = 1150;
		TEXT_WriteText(GIptr, GradientColor[0], &Rect, Text, Scale);
		Yinc = (I == 0) ? 70 : 40;
		Rect.y += Yinc;
	}
	return(TRUE);
}
