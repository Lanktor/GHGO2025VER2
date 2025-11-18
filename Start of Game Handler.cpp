#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT StartOfGameHandler(PGAME_INFO GIptr)
{
	const  BOOL *KeyState;
	INT                Quit, Keys;
	INT                ButtonIdent;
	SDL_Event          Event;
	extern BUTTON_INFO StartGameButtons[];

	KeyState = SDL_GetKeyboardState(NULL);
	Mix_PlayMusic(GIptr->GI_BkgMusic, -1);
	Mix_VolumeMusic(80);

	GIptr->GI_TARGET_FPS = 80;
	GIptr->GI_FRAME_DELAY = 1000 / GIptr->GI_TARGET_FPS;

	GIptr->GI_SecondsCounter = GIptr->GI_PrevTime = SDL_GetTicks();
	GIptr->GI_FrameCounter = 0;

	KeyState = SDL_GetKeyboardState(NULL);

	SDL_StartTextInput(GIptr->GI_MainWindow);

	for (Quit = FALSE; Quit != TRUE; GIptr->GI_FrameCounter++)
	{
		GIptr->GI_FrameStart = SDL_GetTicks();

		SDL_PumpEvents();

		while (SDL_PollEvent(&Event))
		{
			switch (Event.type)
			{
				case SDL_EVENT_TEXT_INPUT:
					START_ProcessPlayerNameEntry(GIptr, &Event);
					printf("Character [%s]\n", Event.text.text);
				break;

				case SDL_EVENT_KEY_DOWN:
					if (Event.key.scancode == SDL_SCANCODE_ESCAPE)
					{
						START_CreateNewGame(GIptr);
						Quit = TRUE;
					}

					if (Event.key.scancode == SDL_SCANCODE_RETURN)
					{
						START_CreateNewGame(GIptr);
						Quit = TRUE;
					}
					if (Event.key.scancode == SDL_SCANCODE_BACKSPACE)
					{
						INT Len = strlen(GIptr->GI_PlayerName);
						if (Len != 0)
						{
							GIptr->GI_PlayerName[Len - 1] = 0;
						}

					}
					break;

				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					if (Event.button.button == SDL_BUTTON_LEFT)
					{
						ButtonIdent = BUTTON_ProcessClick(GIptr, StartGameButtons);
						if (ButtonIdent == BUTTON_IDENT_EXIT) EndOfGameHandler(GIptr);
						if (ButtonIdent == BUTTON_IDENT_RULES)
						{
							BUTTON_ResetButtonState(GIptr, StartGameButtons, BUTTON_STATE_UP);
							RulesHandler(GIptr);
						}
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

		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_StartOfGameTexture, NULL, NULL);
		BUTTON_Update(GIptr, StartGameButtons, 212, 424);
		BUTTON_IsButtonHover(GIptr, StartGameButtons);

		START_DisplayName(GIptr);

		SDL_RenderPresent(GIptr->GI_MainRenderer);

		GIptr->GI_FrameTime = SDL_GetTicks() - GIptr->GI_FrameStart;

		if (GIptr->GI_FrameTime < GIptr->GI_FRAME_DELAY) SDL_Delay(GIptr->GI_FRAME_DELAY - GIptr->GI_FrameTime);

		if (SDL_GetTicks() >= GIptr->GI_SecondsCounter + 1000)
		{
			printf("StartOfGameHandler: FPS: [%d]\n", GIptr->GI_FrameCounter);
			GIptr->GI_FrameCounter = 0;
			GIptr->GI_SecondsCounter = SDL_GetTicks();
		}
	}
	return(TRUE);
}

INT START_ProcessPlayerNameEntry(PGAME_INFO GIptr, PSDL_Event EIptr)
{
	CHAR Data;
	INT  Len;

	Len = strlen(GIptr->GI_PlayerName);
	if(Len >= MAX_NAME_LENGTH - 1) return(FALSE);
	Data = EIptr->text.text[0];

	if(
		   (Data >= 'A') && (Data <= 'Z') ||
		   (Data >= 'a') && (Data <= 'z') ||
		   (Data >= '0') && (Data <= '9')
		)
		{
			GIptr->GI_PlayerName[Len] = Data;
		}

	return(TRUE);
}

INT START_DisplayName(PGAME_INFO GIptr)
{
	INT              I, J;
	SDL_FRect        Rect, Dest;
	extern SDL_Color GradientColor[];

	Dest.x = 	TEXT_CalculateCenterText(GIptr, "Player Name", 2, 1920);
	Dest.y = 230;
	TEXT_WriteText(GIptr, GradientColor[0], &Dest, "Player Name", 2);

	Rect.x = 590;
	Rect.y = 300;
	Rect.w = 731;
	Rect.h = 180;

	SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, GradientColor[0].r, GradientColor[0].g, GradientColor[0].b, GradientColor[0].a);
	SDL_RenderFillRect(GIptr->GI_MainRenderer, &Rect);

	memcpy(&Dest, &Rect, sizeof(SDL_FRect));
	Dest.x += 30;
	Dest.y += 65;
	TEXT_WriteText(GIptr, GradientColor[4],&Dest, GIptr->GI_PlayerName, 2);

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

INT START_CreateNewGame(PGAME_INFO GIptr)
{
	GAMEBOARD_Initiate(GIptr);
	DICE_Initiate(GIptr);
	DICE_Roll(GIptr, GIptr->GI_RollData.RI_DiceRolls[GIptr->GI_RollData.RI_CurRoll]);
	GIptr->GI_CurrentScore = 0;
	GIptr->GI_RNGState = SDL_rand_bits();
	GIptr->GI_CurrentTurn = HUMAN_PLAYER;
	return(TRUE);
}