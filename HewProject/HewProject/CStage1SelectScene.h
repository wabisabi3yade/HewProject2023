#pragma once
#include "CScene.h"

class WorldSelectPic;
class CStageSelectPlayer;
class UI;
class ShadowUI;

class CStage1SelectScene :
    public CScene
{
public:

    bool isSceneChanging;   // シーン変わる

    bool c_isHitStage[5]; // それぞれ当たってるか判定する
    bool o_isHitStage[5];  // 前フレームで当たってるか

    //プレイヤー
    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;
    D3DTEXTURE player_waitTexture;

    //ステージ
    D3DBUFFER stageBuffer;
    D3DTEXTURE stage1Texture;
    D3DTEXTURE stage2Texture;
    D3DTEXTURE stage3Texture;
    D3DTEXTURE stage4Texture;
    D3DTEXTURE shadowTexture;

    //テキスト
    D3DBUFFER textBuffer;
    D3DTEXTURE text_world1Texture;
    D3DTEXTURE text_world2Texture;
    D3DTEXTURE text_world3Texture;
    D3DTEXTURE text_world4Texture;

    //文字
    D3DBUFFER wordBuffer;
    D3DTEXTURE word_RightUpTexture;
    D3DTEXTURE word_RightDownTexture;
    D3DTEXTURE word_LeftUpTexture;
    D3DTEXTURE word_LeftDownTexture;
    D3DTEXTURE world1Texture;
    D3DTEXTURE world2Texture;
    D3DTEXTURE world3Texture;
    D3DTEXTURE worldEXTexture;

    //数字
    D3DBUFFER numBuffer;
    D3DTEXTURE numTexture;

    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    CStageSelectPlayer* player;
    WorldSelectPic* stage[5];
    UI* Text[4];
    UI* Word[8];
    UI* Bg;
    UI* World[4];
    UI* Num[4];
    ShadowUI* Shadow[4];

    bool isPlayerMoving;
    bool isOnce;
    bool isUpDown;
    bool isBigSmall;

public:
    CStage1SelectScene();
    ~CStage1SelectScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;

};



