#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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

std::vector<STAGEPOS> CStageMake::StagePos(LoadData _vStage)
{
	float i = 0;
	STAGEPOS pushstagepos;
	for (auto it = _vStage.data.begin(); it < _vStage.data.end(); )
	{
		for (float j = 0; j < _vStage.data.size() / _vStage.numY; j++)
		{
			pushstagepos.pos.x = j;
			pushstagepos.pos.y = i;
			pushstagepos.blockType = (*it);
			BkType = (BlockType)pushstagepos.blockType;
			//stagePos.emplace_back(pushstagepos);
			stagePos.push_back(pushstagepos);
			it++;
		}
		i++;
	}
	return stagePos;
}

