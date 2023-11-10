#pragma once
#include "CObject.h"
class CEffect :
    public CObject
{


public:
    CEffect(D3DBUFFER vb, D3DTEXTURE tex);

    void Update() override;

    void Draw() override;

    ~CEffect();
};

