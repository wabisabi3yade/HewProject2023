#pragma once
#include "CScene.h"
#include <vector>
#include "CGridObject.h"
#define MAXNUM 20

class UI;
class CGridObject;

class CTitleScene :
    public CScene
{
public:
    //ƒ^ƒCƒgƒ‹
    D3DBUFFER titleBuffer;
    D3DTEXTURE titleTexture;
    
    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    D3DBUFFER sweetsBuffer;
    D3DTEXTURE sweetsTexture;

    D3DBUFFER selectBuffer;
    D3DTEXTURE selectTexture;

    UI* Title;
    UI* Sweets[MAXNUM];
    UI* Bg;
    CGridObject* select[2];

    bool isNoMoving;
    bool isOnce;
    bool isRotationSwitch;
    bool isFlash;

    int m_DrawCount;

public:
    CTitleScene();

    ~CTitleScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

