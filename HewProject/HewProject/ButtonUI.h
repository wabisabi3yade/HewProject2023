#pragma once
#include "UI.h"

class ButtonUI
	: public UI
{

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="vb">バッファ{1,2}</param>
	/// <param name="tex">テクスチャ</param>
	ButtonUI(D3DBUFFER vb, D3DTEXTURE tex);
	void Draw() override;
	~ButtonUI();

	/// <summary>
	/// ボタンをハイライトにする（選ばれたボタン）
	/// </summary>
	/// <param name="_isLight"></param>
	void SetHighlight(bool _isLight);
};

