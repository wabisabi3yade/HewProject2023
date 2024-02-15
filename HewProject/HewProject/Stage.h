#pragma once
#include "CScene.h"
#include "StageScene.h"
#include "DebugTable.h"
#include<iostream>
class Stage :
    public CScene
{
    DebugTable* dbgFloorTable; // テスト用
    DebugTable* dbgObjTable; // テスト用

protected:
    // ステージのUIとか
    StageScene* stage; // ステージ全体のオブジェクト
    // csvファイルの名前
    const wchar_t* csvPath;

    D3DTEXTURE backTex[4];

    D3DBUFFER backBuffer;

    CObject* back;
public:
    /// <summary>
    /// ステージシーンのコンストラクタ
    /// </summary>
    /// <param name="_csvPath">CSVファイルのパス</param>
    Stage(const wchar_t* _csvPath);


    void Init();

    virtual void Update();
    virtual void LateUpdate();
    virtual void Draw();

    virtual ~Stage();
};

