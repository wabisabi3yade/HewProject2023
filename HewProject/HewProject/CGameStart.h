#pragma once
#include "CScene.h"

class UI;

class CGameStart :
    public CScene
{
public:
    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    UI* Bg;

public:
    CGameStart();

    ~CGameStart();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

