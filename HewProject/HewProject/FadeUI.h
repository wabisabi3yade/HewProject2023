#pragma once
#include "UI.h"
class FadeUI :
    public UI
{
    Vector3 offset; // ����W����ǂꂾ�����ɍs���Ă邩
    Vector3 basePos;    // ����W

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

