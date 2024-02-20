#pragma once
#include "Stage.h"
class Stage11 :
    public Stage
{

    D3DTEXTURE tex;

public:
    Stage11();

    void Update() override;

    void Draw() override;
    ~Stage11();
};

