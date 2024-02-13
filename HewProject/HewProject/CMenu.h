#pragma once
#include "CScene.h"

#define MAXNUM_HELP 10

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

    D3DBUFFER LRBuffer;
    D3DTEXTURE LRTexture;
    D3DTEXTURE BTexture;

    UI* Bg;
    UI* Pause;
    ButtonSelect* selectControl;
    ButtonSelect* helpControl;
    ButtonSelect* help_2PageControl;
    ButtonUI* Message[3];
    ButtonUI* helpMessage[MAXNUM_HELP];
    UI* Rule[MAXNUM_HELP];
    UI* LR_Button[2];
    UI* B_Button;

    bool isHelp;
    bool isMenu;
    bool isOnce;
    bool isButton;
    bool isExplanation;
    bool isChangeExplanation;
    int nRule;

public:
    CMenu();

    ~CMenu();
    
    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

