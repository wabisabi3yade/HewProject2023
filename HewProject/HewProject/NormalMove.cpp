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
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::START,static_cast<int>(player->GetState()));
	Vector2 forwardPosXY = { forwardPos.x, forwardPos.y };

	// 奥側に行くかどうか
	bool backMove = false;

	// 奥側に行くときの行動の順番
	// �@ ISOME_BACKMOVE足す　（同じ横列の↑にあるオブジェクトより奥に移動するのでオブジェクトより奥にする）
	// �A移動先に到着するとその床に合わせたZ座標に合わせる
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
				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				pos.z -= 0.000001f;
				scale.x *= HEART_SCALE;
				scale.y *= HEART_SCALE;
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::HEART, false);

				pos = player->mTransform.pos;
				scale = player->mTransform.scale;
				pos.z -= 0.000001f;
				pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
				scale.x *= SMOKE_SCALE;
				scale.y *= SMOKE_SCALE;
				// 食べ終わったら移動できるようにする
				player->dotween->DelayedCall(EAT_TIME, [&,pos,scale]()
					{
						MoveAfter();
						player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_G, false);
						player->EatEnd();
						player->EatCake();
						player->GetPlayerAnim()->StopWalk(player->GetDirection());
						player->ChangeTexture(Player::ANIM_TEX::WAIT);
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
				player->ChangeTexture(Player::ANIM_TEX::EAT_CHILI);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						player->EatChilli();
						player->EatEnd();
						MoveAfter();
						if (player->GetCalorie() < 6)
						{
							Vector3 pos = player->mTransform.pos;
							Vector3 scale = player->mTransform.scale;
							pos.z -= 0.000001f;
							pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
							scale.x *= SMOKE_SCALE;
							scale.y *= SMOKE_SCALE;
							player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
						}
						player->GetPlayerAnim()->StopWalk(player->GetDirection());
						player->ChangeTexture(Player::ANIM_TEX::WAIT);
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

				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						MoveAfter();
						player->GetPlayerAnim()->StopWalk(player->GetDirection());
						player->ChangeTexture(Player::ANIM_TEX::WAIT);
					});
			});
		break;

	case CGridObject::BlockType::CHOCOCRACK:
	{
		WalkStart();
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);
		player->dotween->OnComplete([&]()
			{
				//画面外まで移動するようにYをマクロで定義して使用する
				WalkAfter();

				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
				fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				pos.z -= 0.000001f;
				scale.x *= MARK_SCALE;
				scale.y *= MARK_SCALE;
				player->dotween->DelayedCall(FALL_TIME / 2, [&, pos, scale]()
					{
						player->Fall();
						player->ChangeTexture(Player::ANIM_TEX::WALK);
						player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::MARK, false);
					});
				player->dotween->DoDelay(FALL_TIME);
				player->dotween->Append(fallPos, WALK_TIME, DoTween::FUNC::MOVE_XY);
				switch (player->GetNowFloor())
				{
				case 1:
				case 2:
				case 3:
				{
					player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
					Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
					player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
					if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
					{
						//バウンドする高さを計算　代入
						//player->Fall();
						float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
						player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
						player->dotween->DelayedCall(WALK_TIME + FALL_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
							{
								isFallBound = true;
							});
					}
					player->dotween->DelayedCall(FALLMOVE_TIME + FALL_TIME, [&]()
						{
							player->fallMoveTrriger = true;
						});
				}
				break;
				default:
					break;
				}
			});
		break;
	}
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
				////画面外まで移動するようにYをマクロで定義して使用する
				Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
				fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
				Vector2 fallPosXY;
				fallPosXY.x = fallPos.x;
				fallPosXY.y = fallPos.y;
				player->Fall();
				player->dotween->DoMoveXY(fallPosXY, FALLMOVE_TIME);
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
					if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
					{
						//バウンドする高さを計算　代入
						//player->Fall();
						float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
						player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
						player->dotween->DelayedCall(FALLMOVE_TIME * 3, [&]()
							{
								isFallBound = true;
							});
					}
					player->dotween->DelayedCall(FALLMOVE_TIME, [&]()
						{
							player->fallMoveTrriger = true;
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

	case CGridObject::BlockType::CANNON:
	{
		WalkStart();


		Vector2 junpPos = {};

		Vector3 Vec3JumpPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		junpPos.x = Vec3JumpPos.x;
		junpPos.y = Vec3JumpPos.y;
		player->dotween->DelayedCall(JUMP_TIME / 1.5f, [&]()
			{
				cannonFX = true;
				player->ChangeInvisible();
			});
		// 手前のマスに行くときは先にZ座標を手前に合わせる
		if (_dir != DIRECTION::UP || _dir != DIRECTION::RIGHT)
		{
			player->mTransform.pos.z = forwardPos.z-0.20001f;
		}
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME, junpPos.y + (CANNON_IN_CURVE_POS_Y * player->GetGridTable()->GetGridScale().y));
		player->dotween->Append(forwardPos.z - 0.20001f, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				player->SetGridPos(nextGridPos);
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				player->GetPlayerMove()->InCannon();
			});
	}
	break;
	default:	// 床

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);
		player->dotween->OnComplete([&]() {
			WalkAfter();
			MoveAfter();
			if (player->GetCalorie() < 6)
			{
				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				pos.z -= 0.000001f;
				pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
				scale.x *= SMOKE_SCALE;
				scale.y *= SMOKE_SCALE;
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
			}
			});
		break;
	}
}


void NormalMove::Step()
{
	switch (player->GetPlayerMove()->CheckNextMassType())
	{
	case CGridObject::BlockType::CAKE:

		player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
		player->GetPlayerAnim()->PlayEat(player->GetDirection());
		// 食べ終わったら移動できるようにする
		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
				MoveAfter();

				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				pos.z -= 0.000001f;
				pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
				scale.x *= SMOKE_SCALE;
				scale.y *= SMOKE_SCALE;
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_G, false);
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				player->EatEnd();
				player->EatCake();
				FallAfter();
			});

		break;

	case CGridObject::BlockType::CHILI:
		player->ChangeTexture(Player::ANIM_TEX::EAT_CHILI);
		player->GetPlayerAnim()->PlayEat(player->GetDirection());
		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
				MoveAfter();
				if (player->GetCalorie() < 6)
				{
					Vector3 pos = player->mTransform.pos;
					Vector3 scale = player->mTransform.scale;
					pos.z -= 0.000001f;
					pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
					scale.x *= SMOKE_SCALE;
					scale.y *= SMOKE_SCALE;
					player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
				}
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				player->EatChilli();
				player->EatEnd();
				FallAfter();
			});
		break;

	case CGridObject::BlockType::PROTEIN:

		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
				MoveAfter();
				FallAfter();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
			});
		break;
	case CGridObject::BlockType::CHOCO:
		//WalkStart();
		MoveAfter();
		if (player->GetCalorie() < 6)
		{
			Vector3 pos = player->mTransform.pos;
			Vector3 scale = player->mTransform.scale;
			pos.z -= 0.000001f;
			pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
			scale.x *= SMOKE_SCALE;
			scale.y *= SMOKE_SCALE;
			player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
		}
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		FallAfter();
		break;
	case CGridObject::BlockType::CHOCOCRACK:
	{
		//画面外まで移動するようにYをマクロで定義して使用する			
		if (!isFalling)
		{
			Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
			fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
			Vector3 pos = player->mTransform.pos;
			Vector3 scale = player->mTransform.scale;
			pos.z -= 0.00001f;
			scale.x *= MARK_SCALE;
			scale.y *= MARK_SCALE;
			player->dotween->DelayedCall(FALL_TIME / 2, [&, pos, scale]()
				{
					player->Fall();
					player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::MARK, false);
				});
			player->dotween->DoDelay(FALL_TIME);
			player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);

			player->dotween->OnComplete([&]()
				{
					player->GetPlayerAnim()->StopWalk(player->GetDirection());
					player->ChangeTexture(Player::ANIM_TEX::WAIT);
				});
		}
		player->dotween->DelayedCall(0.1f, [&]()
			{
				FallAfter();
				player->WalkCalorie();
				MoveAfter();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
			});
		break;
	}
	case CGridObject::BlockType::HOLL:
	{
		//WalkStart();
		//ジャンプしてから落ちるように
		//WalkAfter();
		//画面外まで移動するようにYをマクロで定義して使用する
		Vector3 fallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::FLOOR));
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
			//player->Fall();
			player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
			Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
			player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
			if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
			{
				//バウンドする高さを計算　代入
				//player->Fall();
				float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
				player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
				player->dotween->DelayedCall(FALLMOVE_TIME * 3, [&]()
					{
						isFallBound = true;
					});
			}
			player->dotween->DelayedCall(FALLMOVE_TIME, [&]()
				{
					player->fallMoveTrriger = true;
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

		//WalkStart();
		MoveAfter();
		FallAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		//WalkAfter();
		//MoveAfter();
		// ↑にジャンプする

	}
	break;

	case CGridObject::BlockType::CANNON:

		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		player->GetPlayerMove()->InCannon();
		player->SetGridPos(nextGridPos);

		break;

	default:	// 床
		MoveAfter();
		if (player->GetCalorie() < 6)
		{
			Vector3 pos = player->mTransform.pos;
			Vector3 scale = player->mTransform.scale;
			pos.z -= 0.000001f;
			pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
			scale.x *= SMOKE_SCALE;
			scale.y *= SMOKE_SCALE;
			player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
		}
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		FallAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		//player->ChangeTexture(Player::ANIM_TEX::WAIT);
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
