#pragma once
#include "CScene.h"

class CObject;
class CStageSelectPlayer;
class UI;

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

    //�e�L�X�g
    D3DBUFFER textBuffer;
    D3DTEXTURE text_blueTexture;
    D3DTEXTURE text_greenTexture;
    D3DTEXTURE text_pinkTexture;
    D3DTEXTURE text_purpleTexture;

    //����
    D3DBUFFER wordBuffer;
    D3DTEXTURE wordTexture;

    CStageSelectPlayer* player;
    CObject* stage[5];
    UI* Text[4];
    UI* Word;

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



