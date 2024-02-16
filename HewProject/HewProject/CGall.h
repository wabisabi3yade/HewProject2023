#pragma once
#include "CGridObject.h"
#include<iostream>
#include<list>
class CEffect;
class DoTween;
class CGall :
    public CGridObject
{
     std::list<CEffect*> effect;
    bool playEffect;
public:
    std::unique_ptr<DoTween> dotween;
    CGall(D3DBUFFER vb, D3DTEXTURE tex);
    ~CGall();
    void Update();
    void Draw();
    void Open(D3DBUFFER vb , float _animSpeedRate = 1.0f, float _scale = 1.0f);
};

