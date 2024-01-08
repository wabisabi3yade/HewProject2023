#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include "NormalMove.h"
#include "Player.h"

NormalMove::NormalMove(Player* _p)
	: PlayerMove(_p)
{
	// 移動不可能な床の種類を決める
	cantMoveBlock = { 0, 2, 5, 6, 7, 16 };
}

void NormalMove::Move(DIRECTION _dir)
{
	// 移動フラグをtrue
	isMoving = true;
	isMoveStartTrigger = true;

	// 方向を設定する
	player->SetDirection(static_cast<int>(_dir));

	//	移動先のグリッド座標
	nextGridPos = player->GetGridPos();

	switch (_dir)
	{
	case DIRECTION::UP:

		nextGridPos.y += -1;
		break;

	case DIRECTION::DOWN:
		nextGridPos.y += 1;
		break;

	case DIRECTION::RIGHT:
		nextGridPos.x += 1;
		break;

	case DIRECTION::LEFT:
		nextGridPos.x += -1;
		break;
	}

	// ここから先はマスに応じた行動をする
	// 移動先の座標
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CStageMake::BlockType::START);

	// 進んだ先のブロックによって対応するアクションを設定する
	switch (CheckNextMassType())
	{
	case CStageMake::BlockType::CAKE:
		// 移動する
		player->dotween->DoMove(forwardPos, WALK_TIME);
		// 移動し終えたらケーキを食べる
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				// 食べ終わったら移動できるようにする
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						player->EatCake();
						MoveAfter();
					});
			});
		break;

	case CStageMake::BlockType::CHILI:
		player->dotween->DoMove(forwardPos, WALK_TIME);
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						player->EatChilli();
						MoveAfter();
					});
			});
		break;

	case CStageMake::BlockType::HOLL:
		// ↓におちるときのジャンプ
		player->dotween->DoMove(forwardPos, WALK_TIME);
		player->dotween->OnComplete([&]()
			{
				// 穴に落ちた時の処理をする
				// ↓完成していない現状床と同じ処理にしてる
				WalkAfter();
				MoveAfter();
			});
		break;

	case CStageMake::BlockType::GUMI:
		// ↑にジャンプする

		break;

	default:	// 床
		player->dotween->DoMove(forwardPos, WALK_TIME);
		player->dotween->OnComplete([&]() {WalkAfter(); MoveAfter(); });
		break;
	}
}

void NormalMove::CheckCanMove()
{
	PlayerMove::CheckCanMove();
}

NormalMove::~NormalMove()
{
}
