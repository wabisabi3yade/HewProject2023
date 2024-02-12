#pragma once
#include "CGridObject.h"
#include"Player.h"
#include"CannonAnim.h"
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

    std::unique_ptr<DoTween> dotween;
    CCannon(D3DBUFFER vb,D3DTEXTURE tex , GridTable* _nowTable);
    ~CCannon();
    void SetStageSize(CGrid::GRID_XY _set);

    void Update()override;
    void Draw()override;
    void Fire();
    void InPlayer();
    void SetArrow(D3DBUFFER vb, D3DTEXTURE _tex);
    void DirSelect(Player::DIRECTION _dir);
    void CheckCanMove(const GridTable& _nowTable);
    void PlayTurn(int _dir, float _animSpeedRate = 1.0f);
    void PlayReturn(float _animSpeedRate = 1.0f);
    void BlowOff(int _dir);
    bool* GetCanMove() { return &canMoveDir[0]; }
};

