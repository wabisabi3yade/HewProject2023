#pragma once
#include "CGridObject.h"
class CWataame :
    public CGridObject
{
public:
    CWataame(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWataame();
    void Update();
    void Draw();
    void Melt();
};

