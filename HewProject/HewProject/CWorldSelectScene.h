#pragma once
#include "CScene.h"

class CWorldSelectPlayer;
class CGridObject;


class CWorldSelectScene :
    public CScene
{
public:



    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;

    D3DBUFFER stageBuffer;
    D3DTEXTURE stage1Texture;


    CWorldSelectPlayer* player;
    CGridObject* stage[4];




public:
    CWorldSelectScene();

    ~CWorldSelectScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

