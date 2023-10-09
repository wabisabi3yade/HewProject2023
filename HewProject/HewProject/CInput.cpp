#include "CInput.h"
#include <memory.h>

#define KEYBORD 256	// �L�[�{�[�h������͂���Ĕ�������̂��m��256���

// �L�[�������ꂽ�̂��L�^����֐��i�����ɂ͂ǂ̃L�[�������ꂽ����int�^�j
void CInput::SetKeyDownState(int key)
{
	KeyState[key] = true;
}

// �L�[�������ꂽ�̂��L�^����֐�
void CInput::SetKeyUpState(int key)
{
	KeyState[key] = false;
}

//�L�[�v���X���������Ă��邩�Ԃ��֐�
bool CInput::GetKeyPress(int key)
{
	return KeyState[key];
}

bool CInput::GetKeyTrigger(int key)
{
	// 1�t���[���O�̉�����Ԃ�false�ł����݃t���[���̉�����Ԃ�true
	if (!old_KeyState[key] && KeyState[key])
	{
		return true;
	}

	return false;

	// ����������������������
	// return !old_KeyState[key] && KeyState[key];
}

void CInput::UpdateKeyState()
{
	// �w��o�C�g�������������R�s�[����֐�
	memcpy_s(old_KeyState, sizeof(old_KeyState), KeyState, sizeof(KeyState));

	for (int i = 0; i < KEYBORD; i++)
		old_KeyState[i] = KeyState[i];
}
