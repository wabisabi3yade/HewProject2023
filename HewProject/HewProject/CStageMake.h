#pragma once
class CStage;
#include "CLoadStage.h"

struct STAGEPOS
{
	float Pos[2] = {0,0};
};
class CStageMake
{
	int Stagenum = 0;
	std::vector<STAGEPOS> stagePos;
public:
	//int MakeStage();
	int StageNum(std::vector<Stage>);
	std::vector<STAGEPOS> StagePos(std::vector<Stage> _vStage);
	int GetStageNum() { return Stagenum; }
};

