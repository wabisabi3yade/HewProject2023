#pragma once
#include "CGridObject.h"
#include<iostream>
class DoTween;
class CHoll :
    public CGridObject
{
public:
    CHoll(D3DBUFFER vb, D3DTEXTURE tex);
    ~CHoll();
    std::unique_ptr<DoTween> dotween;
    void Update();
    void Draw();
};

