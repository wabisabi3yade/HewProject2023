#pragma once
#include "CScene.h"
#include "Ccontroller.h"

class CTatemizoScene :
    public CScene
{
    D3DBUFFER charBuffer;
    D3DTEXTURE charTexture;
    CObject* charObj;
    Input *controller;


public:
    CTatemizoScene();

    ~CTatemizoScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

