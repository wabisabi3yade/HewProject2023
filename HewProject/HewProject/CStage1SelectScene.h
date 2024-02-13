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

    //�v���C���[
    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;
    D3DTEXTURE player_waitTexture;

    //�X�e�[�W
    D3DBUFFER stageBuffer;
    D3DTEXTURE stage1Texture;
    D3DTEXTURE stage2Texture;
    D3DTEXTURE stage3Texture;
    D3DTEXTURE stage4Texture;
    D3DTEXTURE shadowTexture;

    //�e�L�X�g
    D3DBUFFER textBuffer;
    D3DTEXTURE text_blueTexture;
    D3DTEXTURE text_whiteTexture;
    D3DTEXTURE text_pinkTexture;
    D3DTEXTURE text_purpleTexture;

    //����
    D3DBUFFER wordBuffer;
    D3DTEXTURE word_RightUpTexture;
    D3DTEXTURE word_RightDownTexture;
    D3DTEXTURE word_LeftUpTexture;
    D3DTEXTURE word_LeftDownTexture;

    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    CStageSelectPlayer* player;
    CObject* stage[5];
    UI* Text[4];
    UI* Word[4];
    UI* Bg;
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



