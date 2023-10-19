#pragma once
#include "CScene.h"
#include "DoTween.h"
class CMizunoScene :
    public CScene
{
    D3DBUFFER charBuffer;
    D3DTEXTURE charTexture;
    CObject* charObj;
    DoTween* doToween;
public:
    CMizunoScene();

    ~CMizunoScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

