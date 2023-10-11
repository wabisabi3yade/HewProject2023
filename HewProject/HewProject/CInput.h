#pragma once

// �L�[���͂��Ǘ�����N���X
// �d�g�݁F	WndProc�֐��ŃL�[�������ꂽ�E�����ꂽ�C�x���g����
//			������L�^���Ă����B
//			�L�[�̏�Ԃ𔻒肷��֐����Ă΂ꂽ��A���̋L�^��Ԃ�Ԃ��B
class CInput
{
	// �L�[��Ԃ̋L�^�̈�i�����ꂽ���ǂ����j
	bool KeyState[256] = { false };	// �ŏ���0�ɑ���������̂����Ă����Ƃ��Ƃ�0�ɂ��Ă����

	// 1�t���[���O�̃L�[��Ԃ̋L���̈�
	bool old_KeyState[256] = { false };

public:
	// �����o�[�֐�
	
	// �L�[�������ꂽ�̂��L�^����֐��i�����ɂ͂ǂ̃L�[�������ꂽ����int�^�j
	void SetKeyDownState(int key);

	// �L�[�������ꂽ�̂��L�^����֐�
	void SetKeyUpState(int key);
	
	// �L�[�v���X���������Ă��邩�Ԃ��֐�
	bool GetKeyPress(int key);

	// �L�[�g���K�[���������Ă��邩�Ԃ��֐�
	bool GetKeyTrigger(int key);

	// �Q�[�����[�v�̍Ō�ŃL�[��Ԃ�oldKeyState�ɕۑ�����֐�
	void UpdateKeyState();

};

// �Q�[���̒��Ɉ����new���Ȃ�(�V���O���g���j�̂ł����
// ���̃N���X�̃w�b�_�[�t�@�C���ɏ����Ă�����
// �C���N���[�h���邾���Ŏg����
extern CInput* gInput;