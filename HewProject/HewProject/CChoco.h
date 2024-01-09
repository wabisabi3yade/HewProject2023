#pragma once
#include "CGridObject.h"
class CChoco :
    public CGridObject
{
public:
    CChoco(D3DBUFFER vb, D3DTEXTURE tex);
    ~CChoco();
    void Update();
    void Draw();
};

