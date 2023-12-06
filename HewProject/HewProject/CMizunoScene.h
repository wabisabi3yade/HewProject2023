#pragma once
#include "CScene.h"
#include "DoTween.h"
#include"Ccontroller.h"
#include"CFade.h"
#include"CStageMake.h"
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

    CFade* fade;
    D3DBUFFER fadeBuffer;
    D3DTEXTURE fadeTexture;

    CObject* a[5];
    D3DTEXTURE centerTexture;

    CLoadStage* stage;
    CStageMake* stageMake;

    CObject* stageobj[34];

    Input input;
public:
    CMizunoScene();

    ~CMizunoScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

