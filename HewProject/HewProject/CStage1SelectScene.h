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
    D3DTEXTURE textTexture;

    CStageSelectPlayer* player;
    CObject* stage[4];
    UI* Text;

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



