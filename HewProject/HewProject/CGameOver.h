#pragma once
#include "CScene.h"

#define MAXNUM 2

class UI;

class CGameOver :
    public CScene
{
public:
    
    D3DBUFFER textBuffer;
    D3DTEXTURE textTexture;

    D3DBUFFER textBoxBuffer;
    D3DTEXTURE textBox1Texture;
    D3DTEXTURE textBox2Texture;
    D3DTEXTURE textBox3Texture;

    UI* Text[MAXNUM];
    UI* Message[3];

    bool isOnce;
    bool isOnceBox;
    bool isNoMoving;
    bool isLate;
    int nSelect;
    int m_DrawCount;

public:
    CGameOver();

    ~CGameOver();
    
    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

