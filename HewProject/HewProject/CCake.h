#pragma once
#include "CGridObject.h"
class CCake :
    public CGridObject
{
public:
    CCake(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCake();
    void Update();
    void Draw();
};

