#pragma once
#include "CObject.h"
#include<iostream>
constexpr float ArrowDis = 0.5f;
class DoTween;
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

    DIRECTION dir;

private:
    std::unique_ptr<DoTween> dotween;
    Vector3 scaleUpVal;
    Vector3 scaleDownVal;
    CObject* Owner;
    float stageScale;
public:
    CArrow(D3DBUFFER vb, D3DTEXTURE tex);
    ~CArrow();

    void Update() override;
    void Draw() override;

    void SetArrow(D3DTEXTURE _tex);
    void SetOwner(CObject* _owner ,DIRECTION _dir = NUM, float _scale =1.0f);

    void ScaleLoop();

};

