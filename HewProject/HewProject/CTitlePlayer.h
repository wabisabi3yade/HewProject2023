#pragma once
#include "CGridObject.h"
#include "DoTween.h"

class CTitlePlayer :
    public CGridObject
{
public:
    enum class DIRECTION
    {
        DOWN,	// ��
        LEFT,	// ��
        RIGHT,	// �E
        UP,	// ��
        NUM,
        EVERY,	// �S���ʈړ��\�i�L�����̉摜�̌����͉������j
    };


    std::unique_ptr<DoTween> dotween;

    bool isNormal;
    bool isStopMove;

    int nRandomChara;
    int nAction;

public:
    CTitlePlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CTitlePlayer();
    void Update();
    void Draw();
};

