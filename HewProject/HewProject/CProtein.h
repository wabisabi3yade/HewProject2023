#pragma once
#include "CItem.h"
#include<iostream>
class DoTween;
class CProtein :
    public CItem
{
public:
    CProtein(D3DBUFFER vb, D3DTEXTURE tex);
    ~CProtein();
    std::unique_ptr<DoTween> dotween;
    void Update() override;
    void Draw() override;
    void BlowOff(int _dir);
};

