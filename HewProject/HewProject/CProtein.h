#pragma once
#include "CGridObject.h"
class CProtein :
    public CGridObject
{
public:
    CProtein(D3DBUFFER vb, D3DTEXTURE tex);
    ~CProtein();

    void Update();
    void Draw();
};

