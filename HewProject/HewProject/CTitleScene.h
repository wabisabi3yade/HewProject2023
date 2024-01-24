#pragma once
#include "CScene.h"

class UI;

class CTitleScene :
    public CScene
{
public:
    //�^�C�g��
    D3DBUFFER titleBuffer;
    D3DTEXTURE titleTexture;
    
    UI* Title;

public:
    CTitleScene();

    ~CTitleScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

