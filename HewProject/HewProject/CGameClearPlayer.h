#pragma once
#include "CObject.h"

class CGameClearPlayer :
    public CObject
{
public:
    // ����
    enum class DIRECTION
    {
        DOWN,	// ��
        LEFT,	// ��
        RIGHT,	// �E
        UP,	// ��
        NUM,
        EVERY,	// �S���ʈړ��\�i�L�����̉摜�̌����͉������j
    };

    bool isEatAnim;
    bool isWalkAnim;
public:
    CGameClearPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CGameClearPlayer();
    void Update() override;
    void Draw() override;
};

