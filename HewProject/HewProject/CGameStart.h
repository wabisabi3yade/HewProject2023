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
    D3DTEXTURE needTexture;

    UI* Bg;
    UI* Text;
    UI* Need;
    ProteinUI* Protein;

    Vector3 TextEndPos;
    Vector3 NeedEndPos;
    Vector3 ProteinEndPos;

    bool isProtein;
    int nNumProtein;
    float fProteinZ;
    bool isMoveing;
    bool isWorld1;

public:
    CGameStart(int _num,bool _world1 = false);

    ~CGameStart();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

