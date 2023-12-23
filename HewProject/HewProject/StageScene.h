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
    CGridObject* stageObj;

    D3DBUFFER stageBuffer;
    D3DTEXTURE stageTextureFloor;

    D3DTEXTURE stageTextureFloor2;

    D3DTEXTURE stageTextureWall;
    D3DTEXTURE stageTextureWataame;
    D3DTEXTURE stageTextureCastella;
    D3DTEXTURE stageTextureBaumkuchen;
    D3DTEXTURE stageTextureChocolate;
    D3DTEXTURE stageTextureCake;
    D3DTEXTURE stageTextureChili;
    D3DTEXTURE stageTextureCoin;
    D3DTEXTURE stageTextureGallChest;
    D3DTEXTURE stageTextureGumi;
    D3DTEXTURE stageTextureProtein;

    
public:

    std::vector<CGridObject*> vStageObj;

    StageScene(D3DBUFFER vb, D3DTEXTURE tex);
    ~StageScene();

    void Update();
    void Draw();
    void Z_Sort(std::vector<CGridObject*>& _sortList);
    void Init(const wchar_t* filePath ,float _stageScale);
    Vector3 GetGridToPos(CGrid::GRID_XY _gridXY);
};

