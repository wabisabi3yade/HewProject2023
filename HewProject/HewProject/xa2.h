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
