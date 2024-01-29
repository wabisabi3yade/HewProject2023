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

	// 移動先の座標
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::START);
	Vector2 forwardPosXY = { forwardPos.x, forwardPos.y };

	// 奥側に行くかどうか
	bool backMove = false;

	// 奥側に行くときの行動の順番
	// ① ISOME_BACKMOVE足す　（同じ横列の↑にあるオブジェクトより奥に移動するのでオブジェクトより奥にする）
	// ②移動先に到着するとその床に合わせたZ座標に合わせる
	if (_dir == DIRECTION::UP || _dir == DIRECTION::RIGHT)
	{
		player->mTransform.pos.z += ISOME_BACKMOVE;
	}
	// 手前のマスに行くときは先にZ座標を手前に合わせる
	else
	{
		player->mTransform.pos.z = forwardPos.z;
	}

	// ここから先はマスに応じた行動をする
	// 進んだ先のブロックによって対応するアクションを設定する
	switch (CheckNextMassType())
	{
	case CGridObject::BlockType::CAKE:

		WalkStart();

		// 移動する
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

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

	case CGridObject::BlockType::CHILI:

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);


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

	case CGridObject::BlockType::PROTEIN:

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				player->dotween->DelayedCall(EAT_TIME, [&]() { MoveAfter(); });
			});
		break;

	case CGridObject::BlockType::CHOCOCRACK:

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{

				WalkAfter();
				//画面外まで移動するようにYをマクロで定義して使用する			
				Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
				fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
				player->dotween->DelayedCall(FALL_TIME / 2, [&]()
					{
						player->Fall();
					});
				player->dotween->DoDelay(FALL_TIME);
				player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
			});
		break;

	case CGridObject::BlockType::HOLL:
	{
		WalkStart();
		//ジャンプしてから落ちるように

		Vector2 junpPos = {};

		Vector3 Vec3JumpPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		junpPos.x = Vec3JumpPos.x;
		junpPos.y = Vec3JumpPos.y;
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{

				//WalkAfter();
				//画面外まで移動するようにYをマクロで定義して使用する
				Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
				fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
				Vector2 fallPosXY;
				fallPosXY.x = fallPos.x;
				fallPosXY.y = fallPos.y;
				player->Fall();
				player->dotween->DoMoveXY(fallPosXY, FALLMOVE_TIME);
				//player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
				switch (player->GetNowFloor())
				{
				case 1:
					break;
				case 2:
				case 3:
				{
					player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
					Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
					player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
					player->dotween->DelayedCall(FALLMOVE_TIME, [&]()
						{
							player->fallMoveTrriger = true;
							if (player->GetPlayerMove()->CheckNextFloorType() != CGridObject::BlockType::HOLL)
							{
								//バウンドする高さを計算　代入
								player->Fall();
								float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
								player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
							}
						});

				}

				break;
				default:
					break;
				}
			});


	}
	break;

	case CGridObject::BlockType::GUMI:
	{

		WalkStart();

		Vector2 junpPos = {};


		Vector3 Vec3JumpPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		junpPos.x = Vec3JumpPos.x;
		junpPos.y = Vec3JumpPos.y + 0.3f;
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);
		Vec3JumpPos.y = (FALL_POS_Y * -1.0f) + player->mTransform.scale.y / 2;
		player->dotween->Append(junpPos.y - 0.3f, 0.5f, DoTween::FUNC::MOVE_Y);
		player->dotween->OnComplete([&, Vec3JumpPos]()
			{
				player->dotween->DoDelay(0.3f);
				player->dotween->Append(Vec3JumpPos.y, RISING_TIME, DoTween::FUNC::MOVE_Y);
				player->Rise();
				//player->GetPlayerMove()->RiseStart();
				Vector3 targetPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
				player->dotween->Append(Vector3::zero, RISING_TIME + 0.1f, DoTween::FUNC::DELAY);
				player->dotween->Append(targetPos, RISING_TIME, DoTween::FUNC::MOVE_Y);
				player->dotween->Append(targetPos, RISING_TIME + 0.5f, DoTween::FUNC::MOVECURVE, targetPos.y + 7.0f);
				player->dotween->DelayedCall(RISING_TIME + 0.3f, [&]()
					{
						player->risingMoveTrriger = true;
					});
			});

		// ↑にジャンプする

	}
	break;

	default:	// 床

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);
		player->dotween->OnComplete([&]() {WalkAfter(); MoveAfter(); });
		break;
	}
}


void NormalMove::Step()
{
	switch (player->GetPlayerMove()->CheckNowMassType())
	{
	case CGridObject::BlockType::CAKE:

		//WalkStart();

		// 食べ終わったら移動できるようにする
		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
				player->EatCake();
				MoveAfter();
			});

		break;

	case CGridObject::BlockType::CHILI:

		WalkStart();

		WalkAfter();
		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
				player->EatChilli();
				MoveAfter();
			});
		break;

	case CGridObject::BlockType::PROTEIN:

		player->dotween->DelayedCall(EAT_TIME, [&]() { MoveAfter(); });
		break;
	case CGridObject::BlockType::CHOCO:
		//WalkStart();
		//WalkAfter();
		//MoveAfter();
		break;
	case CGridObject::BlockType::CHOCOCRACK:
	{

		WalkStart();
		//WalkAfter();
		//画面外まで移動するようにYをマクロで定義して使用する			
		Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
		fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
		player->dotween->DelayedCall(FALL_TIME / 2, [&]()
			{
				player->Fall();
			});
		player->dotween->DoDelay(FALL_TIME);
		player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
		break;

	}
	case CGridObject::BlockType::HOLL:
	{
		WalkStart();
		//ジャンプしてから落ちるように
		//WalkAfter();
		//画面外まで移動するようにYをマクロで定義して使用する
		Vector3 fallPos(player->GetGridTable()->GridToWorld(player->GetGridPos(), CGridObject::BlockType::FLOOR));
		fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
		Vector2 fallPosXY;
		fallPosXY.x = fallPos.x;
		fallPosXY.y = fallPos.y;
		player->Fall();
		player->dotween->DoMoveXY(fallPosXY, FALLMOVE_TIME);
		//player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
		switch (player->GetNowFloor())
		{
		case 1:
			break;
		case 2:
		case 3:
		{
			player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
			Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetGridPos(), CGridObject::BlockType::START));
			player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
			//バウンドする高さを計算　代入
			//下が穴でないとき
			float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
			player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
			//if(player->GetGridTable()->)
			player->dotween->DelayedCall(FALLMOVE_TIME, [&]()
				{
					player->fallMoveTrriger = true;
					player->Fall();
				});
		}
		
		break;
		default:
				break;
			}

		
	}
	break;

	case CGridObject::BlockType::GUMI:
	{

		WalkStart();
		//WalkAfter();
		//MoveAfter();
		// ↑にジャンプする

	}
	break;

	default:	// 床

		WalkStart();
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
