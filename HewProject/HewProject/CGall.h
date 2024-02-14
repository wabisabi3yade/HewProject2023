#pragma once
#include "CGridObject.h"
class CEffect;
class CGall :
    public CGridObject
{

    CEffect* effect;
    bool playEffect;
public:
    CGall(D3DBUFFER vb, D3DTEXTURE tex);
    ~CGall();
    void Update();
    void Draw();
};

