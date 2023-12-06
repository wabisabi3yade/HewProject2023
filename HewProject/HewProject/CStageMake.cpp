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
	float i = 0;
	STAGEPOS pushstagepos;
	for (std::vector<Stage>::iterator it = _vStage.begin(); it < _vStage.end(); it++)
	{
		for (float j = 0; j < StageYoko; j++)
		{
			if (_vStage[(int)i].stage[(int)j] != 0)
			{
				pushstagepos.Pos[0] = j;
				pushstagepos.Pos[1] = i;
				stagePos.push_back(pushstagepos);
			}
		}
		i++;
	}
	return stagePos;
}
