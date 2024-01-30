#pragma once
#include "CGridObject.h"
#include"Player.h"
class CArrow;
class CCannon :
    public CGridObject
{
    enum class DIRECTION
    {
        DOWN,
        LEFT,
        RIGHT,
        UP,
        NUM
    };

    CGrid::GRID_XY stageSize = {0};
    void CheckCanMove();
    bool inPlayer;
    bool canMoveDir[static_cast<int>(DIRECTION::NUM)];
    bool IsUse;

    DIRECTION moveDir;

    CArrow* Arrow[static_cast<int>(DIRECTION::NUM)];

public:
    CCannon(D3DBUFFER vb,D3DTEXTURE tex );
    ~CCannon();
    void SetStageSize(CGrid::GRID_XY _set);

    void Update()override;
    void Draw()override;
    void Fire();
    void InPlayer();
    void SetArrow(D3DTEXTURE _tex);
    void DirSelect(Player::DIRECTION _dir);
};

