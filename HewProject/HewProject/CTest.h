#pragma once
#include "CScene.h"
// テストシーン
class CTest :
    public CScene
{
    D3DBUFFER charBuffer;
    D3DTEXTURE charTexture;
    CObject* charObj1;

public:
    CTest();

    ~CTest();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;

};

