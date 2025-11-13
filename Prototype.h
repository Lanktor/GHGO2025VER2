#pragma once

INT EndOfGameHandler(PGAME_INFO GIptr);
INT GameLoop(PGAME_INFO GIptr);
INT InitializeApplication(PGAME_INFO GIptr);
INT RulesHandler(PGAME_INFO GIptr);
INT StartOfGameHandler(PGAME_INFO GIptr);
INT TerminateApplication(PGAME_INFO GIptr);

PSDL_Texture TEXTURE_Load(PGAME_INFO GIptr, PCCHAR FName);

INT DICE_Clear(PGAME_INFO GIptr, PDICE_INFO DIptr);
INT DICE_Initiate(PGAME_INFO GIptr);
INT DICE_InitiateTurn(PGAME_INFO GIptr);
INT DICE_ProcessPick(PGAME_INFO GIptr, PSDL_FRect Mptr);
INT DICE_ProcessRiptide(PGAME_INFO GIptr);
INT DICE_ProcessRoll(PGAME_INFO GIptr);
INT DICE_Render(PGAME_INFO GIptr);
INT DICE_Roll(PGAME_INFO GIptr, PDICE_INFO DIptr);

INT GAMEBOARD_ProcessHover(PGAME_INFO GIptr);
INT GAMEBOARD_ProcessMouseClick(PGAME_INFO GIptr);
INT GAMEBOARD_Render(PGAME_INFO GIptr);
INT GAMEBOARD_RenderBorder(PGAME_INFO GIptr);


INT BUTTON_IsButtonHover(PGAME_INFO GIptr, PBUTTON_INFO BIptr);
INT BUTTON_ResetButtonState(PGAME_INFO GIptr, PBUTTON_INFO BIptr, INT ButtonState);
INT BUTTON_ProcessClick(PGAME_INFO GIptr, PBUTTON_INFO BIptr);
INT BUTTON_Update(PGAME_INFO GIptr, PBUTTON_INFO BIptr, INT DownOffset, INT HoverOffset);

INT TEXT_CalculateCenterText(PGAME_INFO GIptr, const char *Text, INT Scale, INT ItemWidth);
INT TEXT_RenderScore(PGAME_INFO GIptr);
INT TEXT_WriteText(PGAME_INFO GIptr, SDL_Color Color, PSDL_FRect Dest, const char *Text, INT Scale);
INT TEXT_WriteTextRaised(PGAME_INFO GIptr, SDL_Color TopColor, SDL_Color BotColor, PSDL_FRect Dest, const char *Text, INT Scale, INT Offset);

INT TEST_Render(PGAME_INFO GIptr);

INT   UTIL_CheckInsideCircle(PGAME_INFO GIptr, PSDL_FRect Objptr, FLOAT CX, FLOAT CY, FLOAT Rad);
FLOAT UTIL_DegreesToRadians(FLOAT Degrees);
INT   UTIL_DrawCollisionBox(PGAME_INFO GIptr, PSDL_FRect SrceBox, SDL_Color Color, INT BorderSize);
FLOAT UTIL_RadiansToDegrees(FLOAT Radians);
FLOAT UTIL_RandomFloatRange(FLOAT Min, FLOAT Max);
INT   UTIL_RandomIntRange(PUINT State, INT Min, INT Max);

INT SCORE_GetRowCol(PGAME_INFO GIptr, PINT Row, PINT Col);
INT SCORE_ProcessUpper(PGAME_INFO GIptr);
