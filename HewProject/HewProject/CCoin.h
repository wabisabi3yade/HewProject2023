#pragma once
#include "CGridObject.h"
class CCoin :
    public CGridObject
{
public:
    CCoin(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCoin();

    void Update();
    void Draw();
};

