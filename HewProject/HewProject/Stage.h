#pragma once
#include "CScene.h"
#include "StageScene.h"
#include "DebugTable.h"

class Ckcal_gauge;

class Stage :
    public CScene
{
    // ステージのUIとか
    StageScene* stage; // ステージ全体のオブジェクト

    Ckcal_gauge* gauge; // カロリーゲージ

    DebugTable* dbgFloorTable; // テスト用
    DebugTable* dbgObjTable; // テスト用


public:
    /// <summary>
    /// ステージシーンのコンストラクタ
    /// </summary>
    /// <param name="_csvPath">CSVファイルのパス</param>
    Stage(const wchar_t* _csvPath);
    void Update()override;
    void LateUpdate()override;
    void Draw()override;

    ~Stage();
};

