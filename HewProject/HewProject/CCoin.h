#pragma once
#include "CItem.h"
#include<iostream>
class DoTween;
class CCoin :
    public CItem
{
 
public:
    CCoin(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCoin();
    std::unique_ptr<DoTween> dotween;
    void Update() override;
    void Draw() override;
    void BlowOff(int _dir);
};

