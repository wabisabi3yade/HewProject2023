#pragma once
#include "CScene.h"
#include <iostream>

#define MAXNUM_TEXT 8
#define MAXNUM_MESSAGE 3

class ButtonUI;
class CWorldSelectPlayer;
class UI;
class ButtonSelect;

class CGameOver :
    public CScene
{
public:
    
    D3DBUFFER textBuffer;
    D3DBUFFER text_failedBuffer;
    D3DTEXTURE textTexture;

    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;

    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    D3DBUFFER textBoxBuffer;
    D3DTEXTURE textBox1Texture;
    D3DTEXTURE textBox2Texture;
    D3DTEXTURE textBox3Texture;
    D3DTEXTURE textBoxTexture;

    D3DTEXTURE text_restartTexture;
    D3DTEXTURE text_undoTexture;
    D3DTEXTURE text_backTexture;

    UI* Bg;
    UI* Text[MAXNUM_TEXT];
    ButtonUI* Message[MAXNUM_MESSAGE];
    //CWorldSelectPlayer* Player;
    ButtonSelect* selectControl;

    bool isOnce;
    bool isNoMoving;

public:
    CGameOver();

    ~CGameOver();
    
    void Update() override;

    void LateUpdate() override;

    void Draw() override;

    void SetFunc(int _num, std::function<void()> _onComplete);

};

