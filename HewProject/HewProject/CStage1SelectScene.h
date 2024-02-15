#pragma once
#include "CScene.h"

class CObject;
class CStageSelectPlayer;
class UI;
class ShadowUI;

class CStage1SelectScene :
    public CScene
{
public:

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
    D3DTEXTURE worldTexture;

    //数字
    D3DBUFFER numBuffer;
    D3DTEXTURE numTexture;

    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    CStageSelectPlayer* player;
    CObject* stage[5];
    UI* Text[4];
    UI* Word[8];
    UI* Bg;
    UI* World[4];
    UI* Num[4];
    ShadowUI* Shadow[4];

    bool isPlayerMoving;
    bool isOnce;
    bool isUpDown;

public:
    CStage1SelectScene();
    ~CStage1SelectScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;

};



