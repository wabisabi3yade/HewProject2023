#pragma once
#include "CScene.h"

class UI;
class ProteinUI;

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
    ProteinUI* Protein;

    bool isProtein;
    int nNumProtein;
    float fProteinZ;
    bool isMoveing;

public:
    CGameStart(int _num);

    ~CGameStart();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

