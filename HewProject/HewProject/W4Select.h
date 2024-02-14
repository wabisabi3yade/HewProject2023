#pragma once
#include "StageSelect.h"
class W4Select :
    public StageSelect
{
    D3DTEXTURE exTex;

public:
    W4Select();

    void Update() override;

    void Draw() override;

    ~W4Select();
};

