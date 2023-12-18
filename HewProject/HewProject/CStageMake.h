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
        FLOOR,    // ��
        WALL,    // ��
        HOLL,    // ��
        CAKE,    // �P�[�L
        CASTELLA,    // �J�X�e��
        BAUM,    // �o�E���N�[�w��
        START,    // �X�^�[�g
        GALL    // �S�[��
    }; 
private:
    BlockType BkType;
public:

	int StageNum(std::vector<LoadData>, int _stageY);

	//�X�e�[�W�̃f�[�^: Vector<>
	//�X�e�[�W�̉��̐� :int�@
	std::vector<STAGEPOS> StagePos(std::vector<LoadData> _vStage,int _stageY);
	int GetStageNum() { return Stagenum; }
};

