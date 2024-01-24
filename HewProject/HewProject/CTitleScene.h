#pragma once
#include "CScene.h"
#define MAXNUM 5

class UI;

class CTitleScene :
    public CScene
{
public:
    //ƒ^ƒCƒgƒ‹
    D3DBUFFER titleBuffer;
    D3DTEXTURE titleTexture;
    
    D3DBUFFER sweetsBuffer;
    D3DTEXTURE sweetsTexture;

    UI* Title;
    UI* Sweets[MAXNUM];

    bool isNoMoving;
    bool isOnce;
    bool isRotationSwitch;

public:
    CTitleScene();

    ~CTitleScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

