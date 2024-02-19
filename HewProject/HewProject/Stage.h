#pragma once
#include "CScene.h"
#include "StageScene.h"
#include "DebugTable.h"
#include<iostream>
#include "Tutorial.h"
class Stage :
    public CScene
{
    DebugTable* dbgFloorTable; // テスト用
    DebugTable* dbgObjTable; // テスト用

protected:
    short stageNum;

    // ステージのUIとか
    StageScene* stage; // ステージ全体のオブジェクト
    // csvファイルの名前
    const wchar_t* csvPath;

    D3DTEXTURE backTex[4];

    D3DBUFFER backBuffer;

    CObject* back;

    CScene::SCENE_NAME nextStage;

    Tutorial* tutorial = nullptr;
    D3DTEXTURE tutolialTex = NULL;
public:

    Stage();

    /// <summary>
    /// ステージシーンのコンストラクタ
    /// </summary>
    /// <param name="_csvPath">CSVファイルのパス</param>
    Stage(const wchar_t* _csvPath, short int worldNum, CScene::SCENE_NAME _next);


    void Init();

    virtual void Update();
    virtual void LateUpdate();
    virtual void Draw();

    virtual ~Stage();
};

