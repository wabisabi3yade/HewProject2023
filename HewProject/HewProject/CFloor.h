#pragma once
#include "CGridObject.h"
class CFloor :
    public CGridObject
{
public:
    CFloor(D3DBUFFER vb, D3DTEXTURE tex);
    ~CFloor();

    void Update();
    void Draw();
};

