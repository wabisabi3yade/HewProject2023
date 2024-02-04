#pragma once
#include "UI.h"

class ProteinUI
{
	// 全体の座標
	Transform mTransform;

	// ステージにあるプロテインの数
	short stageProMax = 0;

	// 取ったプロテインの数
	short getProtein = 0;

	// 全体のステージの最大数
	static const short max_pro = 3;

	D3DBUFFER buffer;

	// プロテイン取ってない時の丸
	UI* proMark[max_pro];

	// プロテインのスケール
	Vector3 proScale = { 1.4f, 1.4f, 1.0f };
	// プロテインマーク
	UI* protein[max_pro];
	// 下のバー
	UI* bar;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_proteinNum">このステージにあるプロテインの数</param>
	ProteinUI(const int& _proteinNum);
	~ProteinUI();

	void Update();
	// 瞬時に反映
	void SetProtein(const int& _getProtein);

	void AddProtein();

	void Draw();

	void SetPosition(const Vector3& _pos);
};

