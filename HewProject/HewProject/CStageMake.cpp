
//#include "CStageMake.h"
//
//int CStageMake::StageNum(std::vector<LoadData> _vStage, int _stageY)
//{
//	int i = 0;
//	for (std::vector<LoadData>::iterator it = _vStage.begin(); it < _vStage.end(); it++)
//	{
//		for (int j = 0; j < _stageY; j++)
//		{
//			//if ((*it).data != 0)
//			//{
//			//}
//			Stagenum++;
//
//		}
//		i++;
//	}
//	return Stagenum;
//}
//
//std::vector<STAGEPOS> CStageMake::StagePos(LoadData _vStage)
//{
//	float i = 0;
//	STAGEPOS pushstagepos;
//	for (auto it = _vStage.data.begin(); it < _vStage.data.end(); )
//	{
//		for (float j = 0; j < _vStage.data.size() / _vStage.numY; j++)
//		{
//			pushstagepos.pos.x = j;
//			pushstagepos.pos.y = i;
//			pushstagepos.blockType = (*it);
//			BkType = (BlockType)pushstagepos.blockType;
//			//stagePos.emplace_back(pushstagepos);
//			stagePos.push_back(pushstagepos);
//			it++;
//		}
//		i++;
//	}
//	return stagePos;
//}
//
//int CStageMake::JudgeTypeToCategory(BlockType _type)
//{
//	// �����ŏ��J�e�S���ɂ���
//	Category ret = Category::FLOOR;	// �Ԃ��l
//	switch (_type)
//	{
//		// �I�u�W�F�N�g�Ȃ�
//	case BlockType::WALL:
//	case BlockType::CASTELLA:
//	case BlockType::BAUMHORIZONTAL:
//	case BlockType::BAUMVERTICAL:
//	case BlockType::START:
//	case BlockType::GALL:
//	case BlockType::NONE:
//		ret = Category::OBJECT;
//		break;
//
//		// �A�C�e���Ȃ�
//	case BlockType::CAKE:
//	case BlockType::COIN:
//	case BlockType::PROTEIN:
//	case BlockType::CHILI:
//		ret = Category::ITEM;
//		break;
//	
//		// ���͏����œ����Ă���̂�
//	default:
//		break;
//		
//	}
//
//	return static_cast<int>(ret);
//}
//
