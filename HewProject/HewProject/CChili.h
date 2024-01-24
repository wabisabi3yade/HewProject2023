#pragma once
#include "CItem.h"
#include<iostream>
class DoTween;
class CChili :
    public CItem
{
public:
    std::unique_ptr<DoTween> dotween;
    CChili(D3DBUFFER vb, D3DTEXTURE tex);
    ~CChili();
    void Update();
    void Draw();
    void BlowOff(int _dir);
};

