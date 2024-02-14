#pragma once
#include "CGridObject.h"
#include<iostream>
constexpr float MELT_TIME = 1.0f;


class DoTween;
class CEffect;
class CWataame :
    public CGridObject
{
    CEffect* effect;
public:
    CWataame(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWataame();
    std::unique_ptr<DoTween> dotween;
    void Update();
    void Draw();
    void Melt();
};

