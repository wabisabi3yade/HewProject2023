#pragma once
class CStage;
#include "CLoadStage.h"

struct STAGEPOS
{
	float Pos[2] = {0,0};
	int blockType;
};
class CStageMake
{
	int Stagenum = 0;
	std::vector<STAGEPOS> stagePos;
	std::list<STAGEPOS> stagePosList;
public:

	int StageNum(std::vector<LoadData>, int _stageY);

	//ステージのデータ: Vector<>
	//ステージの横の数 :int　
	std::vector<STAGEPOS> StagePos(std::vector<LoadData> _vStage,int _stageY);
	int GetStageNum() { return Stagenum; }
};

