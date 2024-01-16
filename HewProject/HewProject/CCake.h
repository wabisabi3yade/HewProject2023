#pragma once
#include "CItem.h"
#include "DoTween.h"
#include <iostream>

class CCake :
    public CItem
{
public:
    CCake(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCake();
    void Update() override;
    void Draw() override;
};

