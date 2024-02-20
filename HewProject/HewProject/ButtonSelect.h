#pragma once
#include <vector>
#include "ButtonUI.h"

#define PUSH_SCALETIMES (1.3f)

class ButtonSelect
{
	bool isActive = true;	// 今使われているかどうか
	int pointButtonID = 0;
	int registCnt = 0;	// 登録されているボタンの数

	bool isSlecting = true;

	std::vector<ButtonUI*> buttonRegister;	// 制御するボタンの配列

	bool c_isInput = false;
	bool o_isInput = false;
public:
	ButtonSelect();
	~ButtonSelect();

	// トリガー入力用の更新(ButtonMoveの前に絶対書く!!!)
	void FlagUpdate();

	/// <summary>
	/// ボタンを移動させる
	/// </summary>
	/// <param name="_add">ボタンをいくつ移動させるか（引くときはマイナスの値を指定）</param>
	void ButtonMove(int _add);

	void SetButtonID(int _id);

	void SetFlash();


	// 今指定しているボタンの関数を実行
	void PushButton(bool _isFlash = false);

	/// <summary>
	/// ボタンを登録する
	/// </summary>
	/// <param name="_registButton">登録したいボタンのアドレス</param>
	void Regist(ButtonUI* _registButton);

	void SetActive(bool _set) { isActive = _set; }
	bool GetActive()const { return isActive; }

	int GetPointButton()const { return pointButtonID; }

	// 今指しているボタンにセットされた名前を返す
	int GetPointSceneName() { return buttonRegister[pointButtonID]->GetSceneName(); }
};

