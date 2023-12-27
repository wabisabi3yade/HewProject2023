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
		FLOOR =	1,			// ��				1
		WALL,				// ��				2
		HOLL,				// ��				3
		CAKE,				// �P�[�L			4
		CASTELLA,			// �J�X�e��			5
		BAUM,				// �o�E���N�[�w��	6
		COIN,				// �R�C��			7
		WATAAME,			// �Ȃ���			8
		CHOCO,				// �`���R			9
		GUMI,				// �O�~				10
		PROTEIN,			// �v���e�C��		11
		START,				// �X�^�[�g			12
		GALL				// �S�[��			13
	};
private:
	BlockType BkType;
public:

	int StageNum(std::vector<LoadData>, int _stageY);

	//�X�e�[�W�̃f�[�^: Vector<>
	//�X�e�[�W�̉��̐� :int�@
	std::vector<STAGEPOS> StagePos(LoadData _vStage);
	int GetStageNum() { return Stagenum; }
};

