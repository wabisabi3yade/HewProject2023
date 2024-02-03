#pragma once
#include "UI.h"

class ButtonUI
{
	UI* text = nullptr;
	UI* button = nullptr;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_buttonBuffer">ボタンのバッファ</param>
	/// <param name="_buttonTex">ボタンのテクスチャ</param>
	/// <param name="_textBuffer">テキストのバッファ</param>
	/// <param name="_textTex">テキストのテクスチャ</param>
	ButtonUI(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex,D3DBUFFER _textBuffer, D3DTEXTURE _textTex);
	~ButtonUI();

	void Update();

	void Draw();
	
	/// <summary>
	/// ボタンをハイライトにする（選ばれたボタン）
	/// </summary>
	/// <param name="_isLight">赤くするかどうか</param>
	void SetHighlight(bool _isLight);

	void SetScale(const Vector3& _scale);

	void SetPosition(const Vector3& _scale);
};

