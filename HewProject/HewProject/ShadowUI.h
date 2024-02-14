#pragma once
#include "UI.h"
class ShadowUI :
    public UI
{
    UI* shadow = nullptr;
    Vector2 shadowOffset = Vector2::zero;

public:
    ShadowUI(D3DBUFFER vb, D3DTEXTURE tex);
    ~ShadowUI();

    void Update() override;

    void Draw() override;

    void SetShadowOffset(const Vector2& _offset);

    void SetBuffer(D3DBUFFER _vb) override;
    void SetTexture(D3DTEXTURE _tex) override;
};

