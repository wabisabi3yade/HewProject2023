#pragma once
#include "CItem.h"
#include "DoTween.h"

class CChili :
    public CItem
{
public:
    CChili(D3DBUFFER vb, D3DTEXTURE tex);
    ~CChili();
    void Update();
    void Draw();
};

