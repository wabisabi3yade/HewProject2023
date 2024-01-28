#pragma once
#include <iostream>
#include "Vector3.h"
#include <vector>
#include "GridTable.h"

#define WALK_TIME (1.0f)	// 歩くときの移動時間

class Player;

class PlayerMove
{

public:
	// 方向
	enum class DIRECTION
	{
		DOWN,
		LEFT,
		RIGHT,
		UP,
		NUM
	};

protected:
	Player* player;	// プレイヤークラスのポインタ

	bool canMoveDir[static_cast<int>(DIRECTION::NUM)];	// 移動可能である方向

	bool cannonMoveDir[static_cast<int>(DIRECTION::NUM)];

	bool isMoving;	// 移動可能フラグ

	bool isMoveStartTrigger;	// 動き始めたフラグ

	bool isMovingTrigger;	// isMove = true->falseに変わった瞬間だけtrue

	bool isWalkEnd;	// 歩き終わった瞬間true

	bool isWalking_old;	//	前

	bool isWalking_now;	//　今

	bool isFalling;

	bool isRising;

	CGrid::GRID_XY nextGridPos;	// 移動先の座標（MoveAfterでプレイヤーのグリッド座標に更新している）

	std::vector<int> cantMoveBlock;	// 移動できない床の種類を保持

public:
	PlayerMove(Player* _p);

	// 入力関数
	void Input();
	// フラグを初期化する
	void FlagInit();
	// 入力されると移動を行う関数
	virtual void Move(DIRECTION _dir) = 0;

	virtual void Step() =  0 ;

	// 歩き終わった後にする処理（歩き終わって食べるアニメーションをしたりする）
	virtual void WalkAfter();

	// 完全に移動が終わった後にする処理（次に進む方向をここできめたりする）
	// 引数　移動先のグリッド座標
	virtual void MoveAfter();

	void WalkStart();

	void  FallStart();

	void RiseStart();
	//落ち終わったあとにする処理
	virtual void FallAfter();

	virtual void RiseAfter();

	void InCannon();

	void CannonMoveStart();

	void CannonMove();

	// プレイヤーの移動先の座標にあるマスの種類を取得する
	// オブジェクト優先→なにもないなら床の種類が帰ってくる
	// 間違えているかもしれないっす・・・
	CGridObject::BlockType CheckNextMassType();

	// 移動先のプレイヤーのグリッド座標にある物の種類を取得する
	CGridObject::BlockType CheckNextObjectType();

	// 移動先のプレイヤーのグリッド座標にある床の種類を取得する
	CGridObject::BlockType CheckNextFloorType();

	CGridObject::BlockType CheckNowFloorType();

	CGridObject::BlockType CheckNowObjectType();

	CGridObject::BlockType CheckNowMassType();

	// どの方向に移動ができるか取得する関数
	virtual void  CheckCanMove() = 0;

	virtual ~PlayerMove();

	CGrid::GRID_XY GetNextGridPos() const { return nextGridPos; };

	void SetNextGridPos(const CGrid::GRID_XY _nextGirdPos) { nextGridPos = _nextGirdPos; }

	bool GetIsMoving()const { return isMoving; }
	bool GetIsMoveStart()const { return isMoveStartTrigger; }
	bool GetIsMoveTrigger() const { return isMovingTrigger; }
	bool GetIsWalkEnd() const { return isWalkEnd; }
	bool GetIsWalk_Now() const { return isWalking_now; }
	bool GetIsWalk_Old() const { return isWalking_old; }
	bool GetIsFalling()const { return isFalling; }
	bool GetIsRising()const { return isRising; }
	bool* GetCanMoveDir() { return &canMoveDir[0]; }
};

