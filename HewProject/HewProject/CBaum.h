#pragma once
#include "CGridObject.h"
class CBaum :
    public CGridObject
{

public:
    CBaum(D3DBUFFER vb ,D3DTEXTURE tex);
    ~CBaum();

    void Update();
    void Draw();
};

