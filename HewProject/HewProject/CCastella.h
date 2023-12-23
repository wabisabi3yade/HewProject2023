#pragma once
#include "CGridObject.h"
class CCastella :
    public CGridObject
{
public:
    CCastella(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCastella();
    void Update();
    void Draw();
};

