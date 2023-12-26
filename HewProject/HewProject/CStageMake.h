#pragma once
class CStage;
#include "CLoadStage.h"

struct POS
{
	float x, y;
};
struct STAGEPOS
{
	POS pos = {};
	int blockType;
};
class CStageMake
{
	int Stagenum = 0;
	std::vector<STAGEPOS> stagePos;
public:
	enum BlockType
	{
		FLOOR,			// 床				0
		WALL,			// 壁				1
		HOLL,			// 穴				2
		CAKE,			// ケーキ			3
		CASTELLA,		// カステラ			4
		BAUM,			// バウムクーヘン	5
		COIN,			// コイン			6
		WATAAME,		// 綿あめ			7
		CHOCO,			// チョコ			8
		GUMI,			// グミ				9
		PROTEIN,		// プロテイン		10
		START,			// スタート			11
		GALL			// ゴール			12
	};
private:
	BlockType BkType;
public:

	int StageNum(std::vector<LoadData>, int _stageY);

	//ステージのデータ: Vector<>
	//ステージの横の数 :int　
	std::vector<STAGEPOS> StagePos(LoadData _vStage);
	int GetStageNum() { return Stagenum; }
};

