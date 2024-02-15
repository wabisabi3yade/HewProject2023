#pragma once
#include "CGridObject.h"
#include<iostream>
#include<list>
class CEffect;
class CGall :
    public CGridObject
{

     std::list<CEffect*> effect;
    bool playEffect;
public:
    CGall(D3DBUFFER vb, D3DTEXTURE tex);
    ~CGall();
    void Update();
    void Draw();
    void Open(D3DBUFFER vb , float _animSpeedRate = 1.0f);
};

