#pragma once
#include"CScene.h"
#include"CStageMake.h"
#include"CLoadStage.h"
#include"Ccontroller.h"
#include"CFade.h"
#include<vector>
#include<list>
#include"CGridObject.h"
class StageScene :
    public CObject
{
private:

    int StageBlockNum;

    CLoadStage* stage;
    CStageMake* stageMake;
    std::vector<STAGEPOS> stagePos;
    const wchar_t* CsvPath[PathLength] = {L"asset/mizuno/Stage.csv"};

    D3DBUFFER stageBuffer;
    D3DTEXTURE stageTexture;


    D3DTEXTURE stageTexture2;

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
    
public:

    std::vector<CGridObject*> vStageObj;

    StageScene(D3DBUFFER vb, D3DTEXTURE tex);
    ~StageScene();

    void Update();
    void Draw();
    void Z_Sort(std::vector<CGridObject*>& _sortList);
    void Init();
    Vector3 GetGridToPos(CGrid::GRID_XY _gridXY);
};

