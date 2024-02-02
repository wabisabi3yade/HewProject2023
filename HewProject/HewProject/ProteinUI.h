#pragma once

class UI;

class ProteinUI
{
	// ステージにあるプロテインの数
	short stageProMax;

	// 全体のステージの最大数
	static const short max_pro = 3;
	// プロテイン取ってない時の丸
	UI* circle[max_pro];

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

	void Draw();
};

