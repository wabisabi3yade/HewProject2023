//#pragma once
//class CStage;
//#include "CLoadStage.h"
//
//struct POS
//{
//	float x, y;
//};
//struct STAGEPOS
//{
//	POS pos = {};
//	int blockType;
//};
//class CStageMake
//{
//	int Stagenum = 0;
//	std::vector<STAGEPOS> stagePos;
//public:
//	//enum class BlockType
//	//{
//	//	FLOOR = 1,		// ��				1
//	//	WALL,			// ��				2
//	//	HOLL,			// ��				3
//	//	CAKE,			// �P�[�L			4
//	//	CASTELLA,		// �J�X�e��			5
//	//	BAUMHORIZONTAL,	// �o�E���N�[�w���c	6
//	//	BAUMVERTICAL,	// �o�E���N�[�w����	7
//	//	COIN,			// �R�C��			8
//	//	WATAAME,		// �Ȃ���			9
//	//	CHOCO,			// �`���R			10
//	//	CHOCOCRACK,		// �`���R�Ђ�		11
//	//	GUMI,			// �O�~				12
//	//	PROTEIN,		// �v���e�C��		13
//	//	CHILI,			// �Ƃ����炵		14
//	//	START,			// �X�^�[�g			15
//	//	GALL,			// �S�[��			16
//	//	CASTELLA_FLOOR,	// �J�X�e���̏�		17
//	//	NONE = 99,
//	//};
//
//	//// �X�e�[�W�̃I�u�W�F�N�g�̋敪
//	//enum class Category
//	//{
//	//	FLOOR,	// ��
//	//	ITEM,	// �A�C�e��(�P�[�L�A�Ƃ����炵�A���_���Ƃ�)
//	//	OBJECT	// �A�C�e���ȊO�̃I�u�W�F�N�g(�o�E���N�[�w���A�ǂƂ�)
//	//};
//private:
//	/*BlockType BkType;*/
//public:
//
//	int StageNum(std::vector<LoadData>, int _stageY);
//
//	//�X�e�[�W�̃f�[�^: Vector<>
//	//�X�e�[�W�̉��̐� :int�@
//	std::vector<STAGEPOS> StagePos(LoadData _vStage);
//	int GetStageNum() { return Stagenum; };
//
//	//// ���̃u���b�N�̃^�C�v�����̃J�e�S���[����Ԃ�
//	//static int JudgeTypeToCategory(BlockType _type);
//};
//
