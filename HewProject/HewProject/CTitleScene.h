#pragma once
#include "CScene.h"
#include <vector>
#include "CGridObject.h"
#define MAXNUM 20

class UI;
class CGridObject;
class ButtonUI;

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

    D3DBUFFER buttonBuffer;
    D3DTEXTURE buttonTexture;

    UI* Title;
    UI* Sweets[MAXNUM];
    UI* Bg;
    ButtonUI* select[2];

    bool isNoMoving;
    bool isOnce;
    bool isRotationSwitch;
    bool isFlash;

public:
    CTitleScene();

    ~CTitleScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

