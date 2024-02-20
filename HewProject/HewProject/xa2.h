//=============================================================================
//
// サウンド処理 [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>
//=======================追加したBGM,SEの数下に追加===========================//
//=============================サウンドファイル===============================//
//============================================================================//
typedef enum
{
	NONE = -1,		// なにもなし

	// BGM
	B_Title,
	B_WORLDSELECT,
	B_STAGESELECT,
	B_WORLD1,
	B_WORLD2,
	B_WORLD3,
	B_WORLDEX,
	B_MACCHO,

	// 効果音
	S_PUSHBUTTON,
	S_MOVEBUTTON,
	S_PUSH_STAGEBTN,
	S_CHOCO_BREAK,
	S_COIN,
	S_DOWN,
	S_EAT,
	S_FADE_IN,
	S_FLY_BATABATA,
	S_JUMP_GUMI,
	S_JUMP_UP,
	S_MACHO_WALK,
	S_SHOT,
	S_TUTORIAL,
	S_WALK,
	S_WATAAME,
	S_BIKKURI,
	S_DAGEKI,
	S_GAMECLRAR,
	S_GAMEOVER,
	S_JUNP,
	S_PROTEIN_DRINK,
	S_SYASIN,
	S_TEXT,
	S_TEXIN,
	S_TYAKUTI,
	S_YAJIRUISI_UP,
	S_CHEST_OPEN,
	S_CHEST_PUNCH,
	S_FALL,
	S_FLOOR_CHANGE,
	S_INCANNON,
	S_PROTEIN_UP,
	S_CANSEL,
	S_CHANGE,
	S_CHARGE1,
	S_CHARGE2,
	S_CHARGE3,
	S_GOAL,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

// ゲームループ開始前に呼び出すサウンドの初期化処理
HRESULT XA_Initialize(void);

// ゲームループ終了後に呼び出すサウンドの解放処理
void XA_Release(void);

// 引数で指定したサウンドを再生する
void XA_Play(SOUND_LABEL label);

// 引数で指定したサウンドを停止する
void XA_Stop(SOUND_LABEL label);

// 引数で指定したサウンドの再生を再開する
void XA_Resume(SOUND_LABEL label);
//*****************************************************************************
//*****************************************************************************
#endif
