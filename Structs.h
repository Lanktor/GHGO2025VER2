#pragma once

typedef struct _GAME_INFO GAME_INFO, *PGAME_INFO, **PPGAME_INFO;
#define SZ_GAME_INFO sizeof(_GAME_INFO)
#define GAME_INFO_NULL (PGAME_INFO)0

typedef struct _VEC2 VEC2, *PVEC2, **PPVEC2;
#define SZ_VEC2 sizeof(_VEC2)
#define VEC2_NULL (PVEC2)0

typedef struct _BUTTON_INFO BUTTON_INFO, *PBUTTON_INFO, **PPBUTTON_INFO;
#define SZ_BUTTON_INFO sizeof(_BUTTON_INFO)
#define BUTTON_INFO_NULL (PBUTTON_INFO)0

typedef struct _HI_SCORE HI_SCORE, *PHI_SCORE, **PPHI_SCORE;
#define SZ_HI_SCORE sizeof(_HI_SCORE)
#define HI_SCORE_NULL (PHI_SCORE)0


typedef struct _PLAYER_INFO PLAYER_INFO, *PPLAYER_INFO, **PPPLAYER_INFO;
#define SZ_PLAYER_INFO sizeof(_PLAYER_INFO)
#define PLAYER_INFO_NULL (PPLAYER_INFO)0

typedef struct _DICE_INFO DICE_INFO, *PDICE_INFO, **PPDICE_INFO;
#define SZ_DICE_INFO sizeof(_DICE_INFO)
#define DICE_INFO_NULL (PDICE_INFO)0

typedef struct _ROLL_INFO ROLL_INFO, *PROLL_INFO, **PPROLL_INFO;
#define SZ_ROLL_INFO sizeof(_ROLL_INFO)
#define ROLL_INFO_NULL (PROLL_INFO)0

typedef struct _GAMEBOARD_INFO GAMEBOARD_INFO, *PGAMEBOARD_INFO, **PPGAMEBOARD_INFO;
#define SZ_GAMEBOARD_INFO sizeof(_GAMEBOARD_INFO)
#define GAMEBOARD_INFO_NULL (PGAMEBOARD_INFO)0

struct _DICE_INFO
{
	INT       DI_SaveIdent;
	INT       DI_CurIdent;
	INT       DI_Flag;
	INT       DI_HoverFlag;
	SDL_FRect DI_Pos;
};

struct _ROLL_INFO
{
	INT        RI_RipTidesRemaining;
	INT        RI_CurRoll;
	DICE_INFO  RI_DiceRolls[MAX_ROLLS][MAX_DICE];
	INT        RI_Flag;
	PSDL_FRect RI_DiceSrce;
	PSDL_FRect RI_DiceSrceHover;
};

struct _GAMEBOARD_INFO
{
	PSDL_FRect  GBI_NormalSrce;
	PSDL_FRect  GBI_HiliteSrce;
	SDL_FRect   GBI_Dest;
	FLOAT       GBI_TextOffsetX;
	FLOAT       GBI_TextOffsetY;
	const char  GBI_Text[30];
	INT         GBI_Flag;
	INT         GBI_Score;
	INT         GBI_ScoredFlag;
};

struct _PLAYER_INFO
{
	FLOAT       PI_Scale;
};

struct _BUTTON_INFO
{
	INT       BI_Ident;
	INT       BI_State;
	INT       BI_TextXOffset;
	INT       BI_TextYOffset;
	SDL_FRect BI_Srce;
	SDL_FRect BI_Dest;
	char      BI_Text[64];
};

struct _HI_SCORE
{
	CHAR HS_Name[MAX_NAME_LENGTH + 1];
	INT  HS_Score;
};

struct _GAME_INFO
{
	INT           GI_CurrentScore;
	INT           GI_CurrentLevel;
	INT           GI_ScreenWidth;
	INT           GI_ScreenHeight;
	INT           GI_GameVersion;
	INT           GI_Active;
	INT           GI_WinLoseFlag;

	INT           GI_TARGET_FPS;
	INT           GI_FRAME_DELAY;
	FLOAT         GI_DeltaTime;
	UINT64        GI_CurTime;
	UINT64        GI_PrevTime;
	UINT64        GI_FrameStart;
	UINT64        GI_FrameTime;
	UINT64        GI_SecondsCounter;
	UINT64        GI_FrameCounter;
	UINT          GI_RNGState;

	FLOAT         GI_MouseX;
	FLOAT         GI_MouseY;
	INT           GI_MouseState;
	INT           GI_MouseDownFlag;
	INT           GI_MouseUpFlag;

	INT           GI_EOGTestHandler;

	PSDL_FRect    GI_StarField;

	PSDL_Window   GI_MainWindow;
	PSDL_Renderer GI_MainRenderer;
	PMix_Music    GI_BkgMusic;

	PLAYER_INFO   GI_Player;
	CHAR          GI_PlayerName[MAX_NAME_LENGTH + 1];
	HI_SCORE      GI_HiScoreList[MAX_NAMES];

	ROLL_INFO     GI_RollData;

	PGAMEBOARD_INFO GI_ScoreColumns[5];
	PGAMEBOARD_INFO GI_ScoreCategory;

	PSDL_Texture  GI_MainTexture;
	PSDL_Texture  GI_TextTexture;
	PSDL_Texture  GI_RulesTexture;
	PSDL_Texture  GI_EndOfGameTexture;
	PSDL_Texture  GI_StartOfGameTexture;
	PSDL_Texture  GI_GameBoardTexture;
	PSDL_Texture  GI_BackgroundTexture;

};

