#pragma once
#include "CScene.h"
#include <vector>
#include "CGridObject.h"
#define MAXNUM_CAKE 10
#define MAXNUM_PLAYER 4

class UI;
class CGridObject;
class ButtonUI;
class CTitlePlayer;

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

    D3DBUFFER textBuffer;
    D3DTEXTURE textTexture;
    D3DTEXTURE text_endTexture;

    D3DBUFFER playerBuffer;
    D3DTEXTURE player_normalTexture;
    D3DTEXTURE player_fatTexture;
    D3DTEXTURE player_thinTexture;

    UI* Title;
    UI* Sweets[MAXNUM_CAKE];
    UI* Bg;
    ButtonUI* select[2];
    CTitlePlayer* player[MAXNUM_PLAYER];

    bool isNoMoving;
    bool isOnce;
    bool isRotationSwitch;
    bool isFlash;

    int nRandom;

public:
    CTitleScene();

    ~CTitleScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

