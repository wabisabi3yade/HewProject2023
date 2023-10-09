#pragma once
#include "CScene.h"

#define SELECT_SCENE_NUM (5)

class CSelect :
    public CScene
{
    D3DBUFFER charBuffer;
    D3DTEXTURE charTexture[SELECT_SCENE_NUM];
    CObject* charObj;

public:
    CSelect();
    ~CSelect();

    void Update() override;
    void LateUpdate() override;
    void Draw() override;

};

