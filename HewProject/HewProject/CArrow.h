#pragma once
#include "UI.h"
#include<iostream>
constexpr float ArrowDis = 0.5f;
class DoTweenUI;
class CObject;
class CArrow :
    public UI
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
    std::unique_ptr<DoTweenUI> dotween;
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

    bool GetIsActive()const { return isActive; }
    void Appear(Vector2 _tergetPos, float _appearSpeed);
};

