#pragma once
#include "UI.h"
#include "CalorieMark.h"

// カロリーのゲージ全体のクラス
class CalorieGage
{
    CalorieMark* mark;  // カロリーのマーク（15個分）

    Transform mTransform;   // カロリーゲージ全体の大きさ

public:
    CalorieGage();
    ~CalorieGage();

    void Update();
    void Draw();

    // カロリーゲージ
    void ChangePosition(const Vector3& _pos);
    void ChangeScale(const Vector3& _scale);
};

