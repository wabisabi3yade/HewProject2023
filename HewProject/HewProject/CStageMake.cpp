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

			pushstagepos.pos.x = j;
			pushstagepos.pos.y = i;
			pushstagepos.blockType = (*it).data;
			BkType = (BlockType)pushstagepos.blockType;
			//stagePos.emplace_back(pushstagepos);
			stagePos.push_back(pushstagepos);
			switch (BkType)
			{
			case CStageMake::WALL:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::HOLL:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::CAKE:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::CASTELLA:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::BAUM:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::COIN:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::WATAAME:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::CHOCO:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::GUMI:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::PROTEIN:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			case CStageMake::START:

				break;
			case CStageMake::GALL:
				pushstagepos.blockType = 0;
				stagePos.push_back(pushstagepos);
				break;
			default:
				break;
			}
			it++;
		}
		i++;
	}
	return stagePos;
}

