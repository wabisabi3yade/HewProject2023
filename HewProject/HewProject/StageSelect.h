#pragma once
#include "CScene.h"
#include <vector>
#include "StgButton.h"
#include "ButtonSelect.h"

#define UI_POSZ (0.8f)
#define BTN_OFFSETX (1.2f)	// ボタンごとの差分（X座標）
#define BEGIN_MOVETIME (1.0f)   // 始めの移動時間
#define BEGIN_MOVEMENT_X (7.5f) // 初めの移動量

#define WORLDNAME_OFFSETY (1.5f)	// y軸の差分値

#define SIN_POWER (0.12f)
#define SIN_SPEED (1.0f)

class StageSelect :
    public CScene
{

protected:
    float sinRot = 0.0f;

    bool isBeginFin = false;

    bool isChangeNumTriger = false; // 数字が変わった瞬間

    bool isSceneMoving = false;   // シーン変わっている最中か

    bool isMove = false;

    short stageNum; // ステージの数
  
    short c_pointStage = 1;   // 選んでいるステージの数
    short o_pointStage;

    Vector3 btnScale = { 1.5f, 1.5f, 1.0f };
    Vector3 firstBtnPos = { -7.0f, -2.0f, UI_POSZ };

    D3DTEXTURE stageBtnTex; // ステージのボタンのテクスチャ
    D3DBUFFER stageBtnBuf;  // ステージのボタンのバッファ
    D3DTEXTURE numberTex;
    D3DBUFFER numberBuf;
    std::vector<StgButton*> stgButton;  // ステージボタン
    ButtonSelect* btnSelect; 

    D3DBUFFER oneBuf;   // {1,1}

    D3DTEXTURE stageSmpBackTex; // サンプルの背景のテクスチャ
    UI* stageSmpBack;   
    Vector3 stageSmpPos;

    UI* smp;
    std::vector<D3DTEXTURE> stageSmpTex;    // ステージのサンプルテクスチャ


    D3DTEXTURE backTex;    // 背景
    UI* backGround[3];

    // Aボタン
    D3DTEXTURE startTex;
    UI* startUI;

    // Bボタン
    D3DTEXTURE backButtonTex;
    UI* backUI;

    D3DTEXTURE stageTex;
    UI* stageText;
    Vector3 stageTextPos;
    UI* stageTextBack;


    D3DTEXTURE worldTextTex;   // ワールドの背景
    UI* worldText;  // World
    Vector3 worldTextPos;

    UI* worldNum;   // 数字

    D3DTEXTURE worldNameTex;   // ワールド名
    D3DBUFFER worldNameBuffer;
    UI* worldName[2];   // ワールド名
    Vector3 worldNamePos;
    float worldNameOffsetX;

    D3DTEXTURE btnNumTex;   // ボタン用テクスチャ


    virtual void Input();

    void SmpMove(); // サンプルの移動関数

    virtual void BeginMove();   // 最初の動き

public: 
    StageSelect();

    virtual void Update();

    void LateUpdate() override;

    virtual void Draw();

    virtual ~StageSelect();
};

