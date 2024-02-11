#pragma once
#include "UI.h"
#include <functional>

class ButtonUI
{
	Vector3 ButtonScaleConversion(const Vector3& _scale);
	Vector3 TextScaleConversion(const Vector3& _scale);

protected:
	UI* text = nullptr;
	UI* button = nullptr;

	// ボタンを押されたときの関数を
	std::function<void()> func = nullptr;

	// 灰色状態のときの大きさ
	Vector3 grayState_scale = Vector3::one;

	float textScaleTimes = 0.85f;	// ボタンを1.0とした時のテキストの倍率

	virtual void ScaleLoop(Vector3 _downScale, Vector3 _upScale);
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_buttonBuffer">ボタンのバッファ</param>
	/// <param name="_buttonTex">ボタンのテクスチャ</param>
	/// <param name="_textBuffer">テキストのバッファ</param>
	/// <param name="_textTex">テキストのテクスチャ</param>
	ButtonUI(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex,D3DBUFFER _textBuffer, D3DTEXTURE _textTex);
	virtual ~ButtonUI();

	virtual void Update();

	virtual void Draw();
	
	/// <summary>
	/// ボタンをハイライトにする（選ばれたボタン）
	/// </summary>
	/// <param name="_isLight">赤くするかどうか</param>
	virtual void SetHighlight(bool _isLight);

	virtual void SetScale(const Vector3& _scale);

	virtual void SetPosition(const Vector3& _scale);

	// ボタンを押されたときに行う処理を設定
	void SetFunc(std::function<void()> _setFunction);

	// 設定した関数を実行
	void BeginFunc();

	void MakeDotween();

	DoTweenUI* GetDotween();

};

