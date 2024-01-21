#pragma once
#include "UI.h"
class FadeUI :
    public UI
{
    Vector3 offset; // 基準座標からどれだけ横に行ってるか
    Vector3 basePos;    // 基準座標

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

