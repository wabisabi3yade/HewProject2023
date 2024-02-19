#pragma once
#include "CGridObject.h"
class CEffect;
class CChoco :
    public CGridObject
{
    CEffect* effect;
public:
    CChoco(D3DBUFFER vb, D3DTEXTURE tex);
    ~CChoco();
    void Update();
    void Draw();
    void CRACK();
};

