#pragma once
#include "CScene.h"

class CWorldSelectPlayer;
class CGridObject;
class UI;


class CWorldSelectScene :
    public CScene
{
public:

    //プレイヤー
    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;
    D3DTEXTURE player_stopTexture;

    //ステージ
    D3DBUFFER stageBuffer;
    D3DTEXTURE stage1Texture;


    CWorldSelectPlayer* player;
    UI* stage[4];

    //ステージが移動するフラグ
    bool isStageMove;

public:
    CWorldSelectScene();

    ~CWorldSelectScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

