#pragma once
#include "UI.h"

class ProteinUI
{
	// 全体の座標
	Transform mTransform;

	UI* baseUI;

	Vector3 o_pos;

	bool isMarkActive = true;

	// ステージにあるプロテインの数
	short stageProMax = 0;

	// 取ったプロテインの数
	short getProtein = 0;

	// 全体のステージの最大数
	static const short max_pro = 3;

	D3DBUFFER buffer;

	// 全体の倍率
	Vector2 allScale = { 1.0f, 1.0f };

	// プロテイン取ってない時の丸
	UI* proMark[max_pro];

	// プロテインのスケール
	const Vector3 proScale = { 1.4f, 1.4f, 1.0f };

	float proOffset = 0.0f;

	// プロテインマーク
	UI* protein[max_pro];
	// 下のバー
	UI* bar;

	const Vector3 barScale = { 3.0f, 0.05f, 1.0f };

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_proteinNum">このステージにあるプロテインの数</param>
	ProteinUI(const int& _proteinNum, bool _isMarkActive = true);
	~ProteinUI();

	void Update();
	// 瞬時に反映
	void SetProtein(int _getProtein, bool _isDecade = false);

	void AddProtein();

	void Draw();

	void SetPosition(const Vector3& _pos);

	void SetScale(const Vector2& _pos);

	void SetActive(bool _isActive);

	DoTweenUI* GetDotween() { return baseUI->dotween; }
};

