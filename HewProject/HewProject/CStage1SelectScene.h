#pragma once
#include "CScene.h"

class CObject;
class CStageSelectPlayer;

class CStage1SelectScene :
    public CScene
{
public:
    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;

    D3DBUFFER stageBuffer;
    D3DTEXTURE stage1Texture;

    CStageSelectPlayer* player;
    CObject* stage[4];

public:
    CStage1SelectScene();
    ~CStage1SelectScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;

};



