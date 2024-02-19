#pragma once
#include "Transform.h"
#include "UI.h"

#define MARKNUM_MAX (15)	// 目盛りの最大数

class CalorieMark;

// カロリーゲージのクラス
class CalorieGage_hori
{
	UI* base;

	Vector3 o_pos;
	/*Transform mTransform;*/	// ゲージ全体のトランスフォーム

	D3DBUFFER oneBuffer;
	D3DBUFFER markBuffer;
	D3DBUFFER numBuffer;

	CalorieMark* mark[MARKNUM_MAX];	// 目盛り
	const Vector3 markScale = { 0.3f, 0.8f, 1.0f };	// 目盛りの基準となる大きさ

	static const short calorieDigits = 2;	// カロリーの数字の桁数
	UI* number[calorieDigits];	// 数字のUI
	const Vector3 numScale = { 0.8f, 0.8f, 1.0f };

	UI* rogo;	// リスのロゴ
	const Vector3 rogoScale = { 1.75f, 1.75f, 1.0f };	// ロゴの基準となる大きさ

	UI* back;	// ゲージの背景
	const Vector3 backScale = { 6.0f, 1.0f, 1.0f };	// ロゴの基準となる大きさ

	float mark_offsetX;

	short int calorieNum = 8;

	/// <summary>
	/// 目盛りを変える
	/// </summary>
	/// <param name="_oldNum">変わる前の目盛り</param>
	/// <param name="_add">足される目盛り</param>
	void MarkAdd(const short& _oldNum, const short& _add);

	void NumUISetting();

public:
	CalorieGage_hori();
	~CalorieGage_hori();

	void Update();

	void Draw();

	void SetPosition(const Vector3& _pos);
	void SetScale(const Vector3& _scale);

	/// <summary>
	/// カロリーの数を設定(ケーキ食べるときはここ)
	/// </summary>
	/// <param name="_set">設定したい数</param>
	/// <param name="action">演出ありかどうか(Undoは演出なし)</param>
	void SetCalorie(const short& _set, bool action = true);

	// カロリーを足す(引くときはマイナスの値)　(移動、とうがらしはここ)
	void AddCalorie(const short& _add);

	DoTweenUI* GetDotween() { return base->dotween; }
};

