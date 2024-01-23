#pragma once
#include "UI.h"
class NowLoadingText :
    public UI
{
    enum class TEXT
    {
        N,
        o_1,    // o 1��
        w,
        L,
        o_2,    // o 2�� 
        a,
        d,
        i,
        n,
        g,
        period,
        NUM // ��
    };

    // ������UI
    UI* text[static_cast<int>(TEXT::NUM)];
    // �����������Ƃ��̊p�x
    float degree[static_cast<int>(TEXT::NUM)];


    UI* character;

    D3DBUFFER buffer;

public:
    NowLoadingText();
    ~NowLoadingText();

    void Update() override;
    void Draw() override;

    // �S�̂�Z���W��ݒ肷��
    void SetPosZ(float _setZ);
};

