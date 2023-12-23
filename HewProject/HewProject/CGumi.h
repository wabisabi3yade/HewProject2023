#pragma once
#include "CGridObject.h"
class CGumi :
    public CGridObject
{
public:
    CGumi(D3DBUFFER vb, D3DTEXTURE tex);
    ~CGumi();

    void Update();
    void Draw();
};

