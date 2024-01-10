#pragma once
#include "CItem.h"
#include "DoTween.h"
class CCoin :
    public CItem
{
 
public:
    CCoin(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCoin();

    void Update() override;
    void Draw() override;
};

