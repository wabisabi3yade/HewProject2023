#pragma once
#include "CScene.h"

class UI;

class CGameStart :
    public CScene
{
public:
    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    D3DBUFFER textBuffer;
    D3DTEXTURE textTexture;

    UI* Bg;
    UI* Text;

    bool isProtein;

public:
    CGameStart();

    ~CGameStart();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

