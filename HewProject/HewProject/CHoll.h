#pragma once
#include "CGridObject.h"
class CHoll :
    public CGridObject
{
public:
    CHoll(D3DBUFFER vb, D3DTEXTURE tex);
    ~CHoll();
    void Update();
    void Draw();
};

