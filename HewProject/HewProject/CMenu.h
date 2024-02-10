#pragma once
#include "CScene.h"

class UI;
class ButtonUI;
class ButtonSelect;

class CMenu :
    public CScene
{
public:
    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;
    D3DTEXTURE ruleTexture;

    D3DBUFFER pauseBuffer;
    D3DTEXTURE pauseTexture;

    D3DBUFFER textBuffer;
    D3DTEXTURE text_retryTexture;
    D3DTEXTURE text_helpTexture;
    D3DTEXTURE text_escapeTexture;

    D3DBUFFER textBoxBuffer;
    D3DTEXTURE textBoxTexture;

    UI* Bg;
    UI* Pause;
    ButtonSelect* selectControl;
    ButtonUI* Message[3];
    UI* Rule[1];

    bool isHelp;
    bool isMenu;
    bool isOnce;
    bool isButton;
    int nRule;

public:
    CMenu();

    ~CMenu();
    
    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

