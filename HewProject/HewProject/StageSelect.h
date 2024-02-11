#pragma once
#include "CScene.h"
#include <vector>
#include "StgButton.h"
#include "ButtonSelect.h"

#define UI_POSZ (0.8f)
#define BTN_OFFSETX (1.3f)	// ボタンごとの差分（X座標）

class StageSelect :
    public CScene
{

protected:
    bool isChangeNumTriger = false; // 数字が変わった瞬間

    short stageNum; // ステージの数
  
    short c_pointStage = 1;   // 選んでいるステージの数
    short o_pointStage;

    D3DTEXTURE stageBtnTex; // ステージのボタンのテクスチャ
    D3DBUFFER stageBtnBuf;  // ステージのボタンのバッファ
    D3DTEXTURE numberTex;
    D3DBUFFER numberBuf;
    std::vector<StgButton*> stgButton;  // ステージボタン
    ButtonSelect* btnSelect; 

    D3DBUFFER oneBuf;   // {1,1}

    D3DTEXTURE stageSmpBackTex; // サンプルの背景のテクスチャ
    UI* stageSmpBack;   
    std::vector<D3DTEXTURE> stageSmpTex;    // ステージのサンプルテクスチャ


    D3DTEXTURE backTex;    // 背景
    UI* backGround = nullptr;

    D3DTEXTURE startTex;
    UI* startUI;

    D3DTEXTURE WorldBack;   // ワールドの背景
    D3DTEXTURE WorldNum;    // ワールド〇
    D3DTEXTURE WorkdName;   // ワールド名

    virtual void Input();

    void SmpMove(); // サンプルの移動関数

public:
    StageSelect();

    virtual void Update();

    void LateUpdate() override;

    virtual void Draw();

    virtual ~StageSelect();
};

