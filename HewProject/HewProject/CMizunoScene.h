#pragma once
#include "CScene.h"
#include "DoTween.h"
#include"Ccontroller.h"
class CMizunoScene :
    public CScene
{
    D3DBUFFER charBuffer;
    D3DTEXTURE charTexture;
    CObject* charObj;

    D3DBUFFER charBuffer2;
    D3DTEXTURE charTexture2;
    CObject* charObj2;
    DoTween* doToween;

    Input input;
public:
    CMizunoScene();

    ~CMizunoScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

