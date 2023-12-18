#include "CStageMake.h"

int CStageMake::StageNum(std::vector<LoadData> _vStage, int _stageY)
{
	int i = 0;
	for (std::vector<LoadData>::iterator it = _vStage.begin(); it < _vStage.end(); it++)
	{
		for (int j = 0; j < _stageY; j++)
		{
			//if ((*it).data != 0)
			//{
			//}
				Stagenum++;

		}
		i++;
	}
	return Stagenum;
}

std::vector<STAGEPOS> CStageMake::StagePos(std::vector<LoadData> _vStage, int _stageY)
{
	float i = 0;
	STAGEPOS pushstagepos;
	for (std::vector<LoadData>::iterator it = _vStage.begin(); it < _vStage.end(); )
	{
		for (float j = 0; j < _stageY; j++)
		{
			//if ((*it).data != 0)
			//{
			//}
				pushstagepos.pos.x = j;
				pushstagepos.pos.y = i;
				pushstagepos.blockType = (*it).data;
				//stagePos.emplace_back(pushstagepos);
				stagePos.push_back(pushstagepos);
			it++;
		}
		i++;
	}
	return stagePos;
}

