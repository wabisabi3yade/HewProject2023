#pragma once
#include "CGridObject.h"
#include <iostream>
#include"Player.h"
class DoTween;
class CFloor :
    public CGridObject
{
public:
    CFloor(D3DBUFFER vb, D3DTEXTURE tex);
    ~CFloor();
    std::unique_ptr<DoTween> dotween;
    void Update();
    void Draw();
    void FloorBound();
};

