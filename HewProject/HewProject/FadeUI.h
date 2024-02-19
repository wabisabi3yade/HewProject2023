#pragma once
#include "UI.h"
class FadeUI :
    public UI
{
    Vector3 offset; // Šî€À•W‚©‚ç‚Ç‚ê‚¾‚¯‰¡‚És‚Á‚Ä‚é‚©
    Vector3 basePos;    // Šî€À•W

public:
    FadeUI();
    FadeUI(D3DBUFFER vb, D3DTEXTURE tex);
    ~FadeUI();

    void Update() override;
    void Draw() override;

    void SetBasePos(const Vector3& _setPos);
 
    Vector3 GetOffset()const { return offset; }
    void SetOffset(const Vector3& _offset) { offset = _offset; }
};

