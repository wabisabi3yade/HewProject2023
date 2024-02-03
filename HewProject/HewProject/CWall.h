#pragma once
#include "CGridObject.h"
#include"Player.h"
class DoTween;
class CWall :
    public CGridObject
{
private:
    DoTween *dotween;
public:
    CWall(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWall();

    void Update();
    void Draw();
    void Break(float _breakTime = BREAK_TIME);
};

