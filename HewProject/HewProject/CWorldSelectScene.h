#pragma once
#include "CScene.h"

class CWorldSelectPlayer;
class CGridObject;
class UI;


class CWorldSelectScene :
    public CScene
{
public:

    //�v���C���[
    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;
    D3DTEXTURE player_stopTexture;

    //�X�e�[�W
    D3DBUFFER stageBuffer;
    D3DTEXTURE stage1Texture;


    CWorldSelectPlayer* player;
    UI* stage[4];

    //�X�e�[�W���ړ�����t���O
    bool isStageMove;

public:
    CWorldSelectScene();

    ~CWorldSelectScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

