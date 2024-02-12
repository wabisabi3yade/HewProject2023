#pragma once
#include "CObject.h"
#include"CEffectAnim.h"
class CEffect :
    public CObject
{


public:
    CEffect(D3DBUFFER vb, D3DTEXTURE tex);

    void Update() override;

    void Draw() override;

    virtual ~CEffect();

    bool GetIsPlaying()const { return mAnim->isPlaying; };

    CEffectAnim* GetEffectAnim()const { return dynamic_cast<CEffectAnim*>(mAnim); }
};

