#pragma once
#include "CGridObject.h"
class CGall :
    public CGridObject
{
public:
    CGall(D3DBUFFER vb, D3DTEXTURE tex);
    ~CGall();
    void Update();
    void Draw();
};

