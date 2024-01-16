#pragma once
#include "CGridObject.h"
#include "DoTween.h"

class CChili :
    public CGridObject
{
    DoTween* dotween;
public:
    CChili(D3DBUFFER vb, D3DTEXTURE tex);
    ~CChili();
    void Update();
    void Draw();
};

