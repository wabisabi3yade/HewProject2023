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
		BAUMHORIZONTAL,		// �o�E���N�[�w���c	6
		BAUMVERTICAL,		// �o�E���N�[�w����	7
		COIN,				// �R�C��			8
		WATAAME,			// �Ȃ���			9
		CHOCO,				// �`���R			10
		CHOCOCRACK,			// �`���R�Ђ�		11
		GUMI,				// �O�~				12
		PROTEIN,			// �v���e�C��		13
		CHILI,				// ���h�q			14
		START,				// �X�^�[�g			15
		GALL				// �S�[��			16
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

