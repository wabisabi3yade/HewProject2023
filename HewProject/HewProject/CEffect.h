#pragma once
#include "CObject.h"
#include"CEffectAnim.h"
class CEffect :
    public CObject
{
    int fxType;

public:
    CEffect(D3DBUFFER vb, D3DTEXTURE tex);

    void Update() override;

    void Draw() override;

    virtual ~CEffect();

    bool GetIsPlaying()const { return mAnim->isPlaying; };

    CEffectAnim* GetEffectAnim()const { return dynamic_cast<CEffectAnim*>(mAnim); }

    //effectType‚ðÝ’è‚·‚é
    void SetFxType(int _set) { fxType = _set; }
    int GetFxType()const { return fxType; }
    void SetAlpha(float _set) { this->materialDiffuse.w = _set; }
};

