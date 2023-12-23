#pragma once
#include "CGridObject.h"
class CWall :
    public CGridObject
{
private:

public:
    CWall(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWall();

    void Updata();
    void Draw();
};

