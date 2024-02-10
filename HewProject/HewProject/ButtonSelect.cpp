#include "ButtonSelect.h"
#include "ButtonUI.h"

ButtonSelect::ButtonSelect()
{
}

ButtonSelect::~ButtonSelect()
{
	buttonRegister.clear();
	buttonRegister.shrink_to_fit();
}

void ButtonSelect::FlagUpdate()
{
	o_isInput = c_isInput;
	c_isInput = false;
}

void ButtonSelect::ButtonMove(int _add)
{
	c_isInput = true;

	// 入力された瞬間
	if ( !(c_isInput && !o_isInput) || !isActive) return;
	// 登録しているボタンの数以上を指定すると終了する
	if (abs(_add) > buttonRegister.size()) return;

	// 移動する前にボタンのIDを代入
	int o_buttonID = pointButtonID;
	// 足す
	pointButtonID += _add;

	// なんでか知らんけどsize()だとおかしくなる
	if (pointButtonID >= registCnt)
	{
		// 下回る
		pointButtonID -= buttonRegister.size();
	}
	// 下限
	else if (pointButtonID < 0)
	{
		// 上回る
		pointButtonID = buttonRegister.size() + pointButtonID;
	}

	// 前のボタンのハイライト表示を止める
	buttonRegister[o_buttonID]->SetHighlight(false);
	// 新しく指定したボタンをハイライトさせる
	buttonRegister[pointButtonID]->SetHighlight(true);
}

void ButtonSelect::PushButton()
{
	if (!isActive) return;
	buttonRegister[pointButtonID]->BeginFunc();
}

void ButtonSelect::Regist(ButtonUI* _registButton)
{
	buttonRegister.push_back(_registButton);
	registCnt++;
}
