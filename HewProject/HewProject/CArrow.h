#pragma once
#include "CObject.h"
constexpr float ArrowDis = 0.5f;
class CArrow :
    public CObject
{
public:
    enum DIRECTION
    {
        DOWN,
        LEFT,
        RIGHT,
        UP,
        NUM,
    };

private:

    CObject* Owner;

public:
    CArrow(D3DBUFFER vb, D3DTEXTURE tex);
    ~CArrow();

    void Update() override;
    void Draw() override;

    void SetArrow(D3DTEXTURE _tex);
    void SetOwner(CObject* _owner ,DIRECTION _dir);
};

