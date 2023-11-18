#include "CStageMake.h"

int CStageMake::StageNum(std::vector<Stage> _vStage)
{
	int i = 0;
	for (std::vector<Stage>::iterator it = _vStage.begin(); it < _vStage.end(); it++)
	{
		for (int j = 0; j < StageYoko; j++)
		{
			if (_vStage[i].stage[j] != 0)
			{
				Stagenum++;
				//STAGEPOS pushstagepos;
				//pushstagepos.Pos[0] = {i};
				//pushstagepos.Pos[1] = {j};
				//StagePos.push_back(pushstagepos);
			}
		}
		i++;
	}
	return Stagenum;
}
std::vector<STAGEPOS> CStageMake::StagePos(std::vector<Stage> _vStage)
{
	int i = 0;
	STAGEPOS pushstagepos;
	for (std::vector<Stage>::iterator it = _vStage.begin(); it < _vStage.end(); it++)
	{
		for (int j = 0; j < StageYoko; j++)
		{
			if (_vStage[i].stage[j] != 0)
			{
				pushstagepos.Pos[0] = {i};
				pushstagepos.Pos[1] = {j};
				stagePos.push_back(pushstagepos);
			}
		}
		i++;
	}
	return stagePos;
}
