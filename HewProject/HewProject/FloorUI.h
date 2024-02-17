#pragma once
#include "UI.h"

class FloorUI
{
	short stageFloorNum = 0;  // このステージの最大の階層数

	short nowHilghtFloor = 0;

	static const short max = 3; // 3階まで
	D3DBUFFER buffer;
	UI* floor[max][2];  // UI

	UI* baseUI;

	Vector3 o_pos;

	// 灰色のときの大きさ
	Vector3 grayScale = { 0.5f,0.6f, 1.0f };
	// ハイライトの時の大きさ
	Vector3 highlightScale = { 0.8f,0.96f, 0.8f };

	// 座標設定
	void SetPosition();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_startFloorNum">最初に始まる階層</param>
	/// <param name="_maxNum">最大の階層</param>
	FloorUI(const int& _startFloorNum, const int& _maxNum);

	void Update();

	~FloorUI();

	void Draw();

	// ハイライトさせたい階層を設定
	void SetHighlight(int _set);

	DoTweenUI* GetDotween() { return baseUI->dotween; }
};

