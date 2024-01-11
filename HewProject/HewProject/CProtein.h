#pragma once
#include "CItem.h"
#include "DoTween.h"
class CProtein :
    public CItem
{
public:
    CProtein(D3DBUFFER vb, D3DTEXTURE tex);
    ~CProtein();

    void Update() override;
    void Draw() override;
};

