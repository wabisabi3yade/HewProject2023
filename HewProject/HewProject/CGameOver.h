#pragma once
#include "CScene.h"

#define MAXNUM_TEXT 3

class ButtonUI;
class CWorldSelectPlayer;
class UI;

class CGameOver :
    public CScene
{
public:
    
    D3DBUFFER textBuffer;
    D3DBUFFER text_failedBuffer;
    D3DTEXTURE textTexture;

    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;

    D3DBUFFER textBoxBuffer;
    D3DTEXTURE textBox1Texture;
    D3DTEXTURE textBox2Texture;
    D3DTEXTURE textBox3Texture;
    D3DTEXTURE textBoxTexture;

    D3DTEXTURE text_restartTexture;
    D3DTEXTURE text_undoTexture;
    D3DTEXTURE text_backTexture;

    UI* Text[MAXNUM_TEXT];
    ButtonUI* Message[3];
    CWorldSelectPlayer* Player;

    bool isOnce;
    bool isOnceBox;
    bool isNoMoving;
    bool isLate;
    int nSelect;

public:
    CGameOver();

    ~CGameOver();
    
    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

