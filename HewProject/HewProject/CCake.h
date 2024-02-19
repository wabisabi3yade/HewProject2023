#pragma once
#include "CItem.h"
#include <iostream>
class DoTween;

class CCake :
    public CItem
{
public:
    std::unique_ptr<DoTween> dotween;
    CCake(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCake();
    void Update() override;
    void Draw() override;
    void BlowOff(int _dir);
};

