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
		FLOOR,			// ��				0
		WALL,			// ��				1
		HOLL,			// ��				2
		CAKE,			// �P�[�L			3
		CASTELLA,		// �J�X�e��			4
		BAUM,			// �o�E���N�[�w��	5
		COIN,			// �R�C��			6
		WATAAME,		// �Ȃ���			7
		CHOCO,			// �`���R			8
		GUMI,			// �O�~				9
		PROTEIN,		// �v���e�C��		10
		START,			// �X�^�[�g			11
		GALL			// �S�[��			12
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

