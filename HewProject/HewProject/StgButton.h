#pragma once
#include "ButtonUI.h"
class StgButton
	: public ButtonUI
{
	void ScaleLoop(Vector3 _downScale, Vector3 _upScale) override;

public:
	StgButton(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex, D3DBUFFER _textBuffer, D3DTEXTURE _textTex);

	~StgButton();

	void Update() override;

	void Draw() override;

	/// <summary>
	/// ボタンをハイライトにする（選ばれたボタン）
	/// </summary>
	/// <param name="_isLight">赤くするかどうか</param>
	void SetHighlight(bool _isLight) override;

	void SetScale(const Vector3& _scale) override;

	void SetPosition(const Vector3& _pos) override;

	// ボタンを押されたときに行う処理を設定
	void SetFunc(std::function<void()> _setFunction);

	// 設定した関数を実行
	void BeginFunc();

	// 数字を設定
	void SetNum(short num);
};

