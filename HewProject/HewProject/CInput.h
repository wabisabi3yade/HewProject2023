#pragma once

// キー入力を管理するクラス
// 仕組み：	WndProc関数でキーが押された・離されたイベント時に
//			それを記録していく。
//			キーの状態を判定する関数が呼ばれたら、その記録状態を返す。
class CInput
{
	// キー状態の記録領域（押されたかどうか）
	bool KeyState[256] = { false };	// 最初に0に相当するものを入れておくとあとは0にしてくれる

	// 1フレーム前のキー状態の記憶領域
	bool old_KeyState[256] = { false };

public:
	// メンバー関数
	
	// キーが押されたのを記録する関数（引数にはどのキーが押されたかのint型）
	void SetKeyDownState(int key);

	// キーが離されたのを記録する関数
	void SetKeyUpState(int key);
	
	// キープレスが発生しているか返す関数
	bool GetKeyPress(int key);

	// キートリガーが発生しているか返す関数
	bool GetKeyTrigger(int key);

	// ゲームループの最後でキー状態をoldKeyStateに保存する関数
	void UpdateKeyState();

};

// ゲームの中に一個しかnewしない(シングルトン）のであれば
// そのクラスのヘッダーファイルに書いておけば
// インクルードするだけで使える
extern CInput* gInput;