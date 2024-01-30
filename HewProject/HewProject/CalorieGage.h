#pragma once
#include "UI.h"
#include "CalorieMark.h"

// �J�����[�̃Q�[�W�S�̂̃N���X
class CalorieGage
{
    CalorieMark* mark;  // �J�����[�̃}�[�N�i15���j

    Transform mTransform;   // �J�����[�Q�[�W�S�̂̑傫��

public:
    CalorieGage();
    ~CalorieGage();

    void Update();
    void Draw();

    // �J�����[�Q�[�W
    void ChangePosition(const Vector3& _pos);
    void ChangeScale(const Vector3& _scale);
};

