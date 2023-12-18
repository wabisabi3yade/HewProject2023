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
        FLOOR,    // 床
        WALL,    // 壁
        HOLL,    // 穴
        CAKE,    // ケーキ
        CASTELLA,    // カステラ
        BAUM,    // バウムクーヘン
        START,    // スタート
        GALL    // ゴール
    }; 
private:
    BlockType BkType;
public:

	int StageNum(std::vector<LoadData>, int _stageY);

	//ステージのデータ: Vector<>
	//ステージの横の数 :int　
	std::vector<STAGEPOS> StagePos(std::vector<LoadData> _vStage,int _stageY);
	int GetStageNum() { return Stagenum; }
};

