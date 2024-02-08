#pragma once
#include "CScene.h"

class UI;
class ButtonUI;
class ButtonSelect;

class CGameClear :
    public CScene
{

public:
    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    D3DBUFFER textBuffer;
    D3DTEXTURE textTexture;

    D3DBUFFER textBoxBuffer;
    D3DTEXTURE textBoxTexture;

    D3DTEXTURE text_nextStageTexture;
    D3DTEXTURE text_stageSelectTexture;

    UI* Bg;
    ButtonSelect* selectControl;
    UI* Text[6];
    ButtonUI* Message[2];

    bool isNoMoving;
    bool isOnce;

public:
    CGameClear();

    ~CGameClear();
    
    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

