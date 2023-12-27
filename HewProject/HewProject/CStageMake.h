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
		FLOOR =	1,			// 床				1
		WALL,				// 壁				2
		HOLL,				// 穴				3
		CAKE,				// ケーキ			4
		CASTELLA,			// カステラ			5
		BAUM,				// バウムクーヘン	6
		COIN,				// コイン			7
		WATAAME,			// 綿あめ			8
		CHOCO,				// チョコ			9
		GUMI,				// グミ				10
		PROTEIN,			// プロテイン		11
		START,				// スタート			12
		GALL				// ゴール			13
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

