//=============================================================================
//
// �T�E���h���� [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>
//=======================�ǉ�����BGM,SE�̐����ɒǉ�===========================//
//=============================�T�E���h�t�@�C��===============================//
//============================================================================//
typedef enum
{
	NONE = -1,		// �Ȃɂ��Ȃ�

	// BGM
	B_Title,
	B_WORLDSELECT,
	B_STAGESELECT,
	B_WORLD1,
	B_WORLD2,
	B_WORLD3,
	B_WORLDEX,
	B_MACCHO,

	// ���ʉ�
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
// �v���g�^�C�v�錾
//*****************************************************************************

// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
HRESULT XA_Initialize(void);

// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
void XA_Release(void);

// �����Ŏw�肵���T�E���h���Đ�����
void XA_Play(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h���~����
void XA_Stop(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
void XA_Resume(SOUND_LABEL label);
//*****************************************************************************
//*****************************************************************************
#endif
