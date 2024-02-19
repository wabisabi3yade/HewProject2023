#pragma once
#include "CGridObject.h"
#include"Player.h"
class CEffect;
class DoTween;
class CWall :
    public CGridObject
{
private:
    DoTween *dotween;
    bool isBreak;
    bool isDecrease;
    float time;
    CEffect* effect;
public:
    CWall(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWall();

    void Update();
    void Draw();
    void Break(int _dir ,float _breakTime = BREAK_TIME);
};

