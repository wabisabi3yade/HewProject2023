#pragma once
#include "Stage.h"
class Stage11 :
    public Stage
{

    D3DTEXTURE tex;

    D3DTEXTURE getProteinTex = NULL;
    D3DTEXTURE goChestTex = NULL;

    UI* text;
public:
    Stage11();

    void Update() override;

    void Draw() override;
    ~Stage11();
};

