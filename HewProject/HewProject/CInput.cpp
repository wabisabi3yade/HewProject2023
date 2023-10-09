#include "CInput.h"
#include <memory.h>

#define KEYBORD 256	// キーボードから入力されて反応するのが確か256種類

// キーが押されたのを記録する関数（引数にはどのキーが押されたかのint型）
void CInput::SetKeyDownState(int key)
{
	KeyState[key] = true;
}

// キーが離されたのを記録する関数
void CInput::SetKeyUpState(int key)
{
	KeyState[key] = false;
}

//キープレスが発生しているか返す関数
bool CInput::GetKeyPress(int key)
{
	return KeyState[key];
}

bool CInput::GetKeyTrigger(int key)
{
	// 1フレーム前の押下状態がfalseでかつ現在フレームの押下状態がtrue
	if (!old_KeyState[key] && KeyState[key])
	{
		return true;
	}

	return false;

	// ↓こういう書き方もある
	// return !old_KeyState[key] && KeyState[key];
}

void CInput::UpdateKeyState()
{
	// 指定バイト数分メモリをコピーする関数
	memcpy_s(old_KeyState, sizeof(old_KeyState), KeyState, sizeof(KeyState));

	for (int i = 0; i < KEYBORD; i++)
		old_KeyState[i] = KeyState[i];
}
