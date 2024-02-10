#pragma once
#include "CScene.h"
#include <vector>
#include "StgButton.h"
#include "ButtonSelect.h"
//class ButtonSelect;

class StageSelect :
    public CScene
{

protected:
    bool isChangeNumTriger = false; // 数字が変わった瞬間

    short stageNum = 0; // ステージの数
    
    short pointStage = 1;   // 選んでいるステージの数

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


    D3DTEXTURE Back;    // 背景
    D3DTEXTURE WorldBack;   // ワールドの背景
    D3DTEXTURE WorldNum;    // ワールド〇
    D3DTEXTURE WorkdName;   // ワールド名

    void Input();

public:
    StageSelect();

    virtual void Update();

    void LateUpdate() override;

    virtual void Draw();

    virtual ~StageSelect();
};

