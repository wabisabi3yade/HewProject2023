#pragma once
#include "CGridObject.h"
#include "DoTween.h"
#include <iostream>

class CWorldSelectPlayer :
    public CGridObject
{
public:
    std::unique_ptr<DoTween> dotween;


    bool isNoPush;
    bool isMoving;

    CWorldSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWorldSelectPlayer();
    void Update();
    void Draw();
};

