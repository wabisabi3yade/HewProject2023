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
	//std::list<STAGEPOS> stagePosList;
public:

	int StageNum(std::vector<LoadData>, int _stageY);

	//�X�e�[�W�̃f�[�^: Vector<>
	//�X�e�[�W�̉��̐� :int�@
	std::vector<STAGEPOS> StagePos(std::vector<LoadData> _vStage,int _stageY);
	int GetStageNum() { return Stagenum; }
};

