#pragma once
#include "CGridObject.h"
#include<iostream>
class DoTween;
class CWataame :
    public CGridObject
{
public:
    CWataame(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWataame();
    std::unique_ptr<DoTween> dotween;
    void Update();
    void Draw();
    void Melt();
};

