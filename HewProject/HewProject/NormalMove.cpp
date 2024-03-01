#include "NormalMove.h"
#include "Player.h"
#include"xa2.h"
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
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::START, static_cast<int>(player->GetState()));
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
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
		// 移動する
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		// 移動し終えたらケーキを食べる
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				XA_Play(SOUND_LABEL::S_EAT);
				player->dotween->DelayedCall(0.7f, [&]()
					{
						XA_Play(SOUND_LABEL::S_EAT);
					});
				player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				pos.z += 0.001000f;
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
				player->dotween->DelayedCall(EAT_TIME, [&, pos, scale]()
					{
						MoveAfter();
						XA_Play(SOUND_LABEL::S_CHANGE);
						player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_G, false);
						player->EatEnd();
						player->Stop();
						player->EatCake();
						player->GetPlayerAnim()->StopWalk(player->GetDirection());
						player->ChangeTexture(Player::ANIM_TEX::WAIT);
					});

			});
		break;

	case CGridObject::BlockType::CHILI:

		WalkStart();
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);


		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				XA_Play(SOUND_LABEL::S_EAT);
				player->dotween->DelayedCall(0.7f, [&]()
					{
						XA_Play(SOUND_LABEL::S_EAT);
					});
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
							XA_Play(SOUND_LABEL::S_CHANGE);
							player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
							player->Stop();
						}
						player->GetPlayerAnim()->StopWalk(player->GetDirection());
						player->ChangeTexture(Player::ANIM_TEX::WAIT);
					});
			});
		break;

	case CGridObject::BlockType::PROTEIN:

		WalkStart();
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				XA_Play(SOUND_LABEL::S_PROTEIN_DRINK);
				player->dotween->DelayedCall(0.5f, [&]()
					{
						XA_Play(SOUND_LABEL::S_PROTEIN_DRINK);
					});
				player->ChangeTexture(Player::ANIM_TEX::DRINK);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				WalkAfter();
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
							XA_Play(SOUND_LABEL::S_CHANGE);
							player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
							player->Stop();
						}
						player->EatEnd();
						player->GetPlayerAnim()->StopWalk(player->GetDirection());
						player->ChangeTexture(Player::ANIM_TEX::WAIT);
					});
			});
		break;

	case CGridObject::BlockType::CHOCOCRACK:
	{
		WalkStart();
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
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
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::MARK, false);
				XA_Play(SOUND_LABEL::S_BIKKURI);
				player->dotween->DelayedCall(FALL_TIME / 2, [&]()
					{
						player->Fall();
						XA_Play(SOUND_LABEL::S_FLY_BATABATA);
					});
				player->dotween->DelayedCall(FALL_TIME, [&]()
					{
						XA_Play(SOUND_LABEL::S_FALL);
					});
				player->dotween->DoDelay(FALL_TIME);
				player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);

				player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
				Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
				player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
				if (player->GetNowFloor() != 1)
				{
					if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
					{
						//バウンドする高さを計算　代入
						float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
						player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
						player->dotween->DelayedCall(FALLMOVE_TIME + FALL_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
							{
								XA_Play(SOUND_LABEL::S_TYAKUTI);
								isFallBound = true;
							});
					}
				}
				player->dotween->DelayedCall(FALLMOVE_TIME + FALL_TIME, [&]()
					{
						player->fallMoveTrriger = true;
					});
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
		XA_Play(SOUND_LABEL::S_JUNP);
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				////画面外まで移動するようにYをマクロで定義して使用する

				XA_Play(SOUND_LABEL::S_FALL);
				Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
				fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
				Vector2 fallPosXY;
				fallPosXY.x = fallPos.x;
				fallPosXY.y = fallPos.y;
				player->Fall();
				player->dotween->DoMoveXY(fallPosXY, FALLMOVE_TIME);

				player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
				Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
				player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
				if (player->GetNowFloor() != 1)
				{
					if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
					{
						//バウンドする高さを計算　代入
						float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
						player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
						player->dotween->DelayedCall(FALLMOVE_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
							{
								XA_Play(SOUND_LABEL::S_TYAKUTI);
								isFallBound = true;
							});
					}
				}
				player->dotween->DelayedCall(FALLMOVE_TIME, [&]()
					{
						player->fallMoveTrriger = true;
					});

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
				player->dotween->DelayedCall(0.3f, [&]()
					{
						XA_Play(SOUND_LABEL::S_JUMP_GUMI);
					});
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
		//大砲に入るとき左下に最高地点が高いのを制御する
		float CurvePosControlVal = 1.0f;
		// 手前のマスに行くときは先にZ座標を手前に合わせる
		if (_dir != DIRECTION::UP || _dir != DIRECTION::RIGHT)
		{
			player->mTransform.pos.z = forwardPos.z - 0.20001f;
			CurvePosControlVal = 0.7f;
		}
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME, junpPos.y + (CANNON_IN_CURVE_POS_Y * CurvePosControlVal * player->GetGridTable()->GetGridScale().y));
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
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
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
				XA_Play(SOUND_LABEL::S_CHANGE);
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
				player->Stop();
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

		XA_Play(SOUND_LABEL::S_EAT);
		player->dotween->DelayedCall(0.7f, [&]()
			{
				XA_Play(SOUND_LABEL::S_EAT);
			});
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
				XA_Play(SOUND_LABEL::S_CHANGE);
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_G, false);
				player->EatEnd();
				player->Stop();
				player->EatCake();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				FallAfter();
			});

		break;

	case CGridObject::BlockType::CHILI:
		XA_Play(SOUND_LABEL::S_EAT);
		player->dotween->DelayedCall(0.7f, [&]()
			{
				XA_Play(SOUND_LABEL::S_EAT);
			});
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
					XA_Play(SOUND_LABEL::S_CHANGE);
					player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
					player->Stop();
				}
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				FallAfter();
				player->EatChilli();
				player->EatEnd();
				FallAfter();
			});
		break;

	case CGridObject::BlockType::PROTEIN:

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
					XA_Play(SOUND_LABEL::S_CHANGE);
					player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
					player->Stop();
				}
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
			XA_Play(SOUND_LABEL::S_CHANGE);
			player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
			player->Stop();
		}
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		FallAfter();
		break;
	case CGridObject::BlockType::CHOCOCRACK:
	{

		if (!isFalling)
		{

			WalkStart();

			//画面外まで移動するようにYをマクロで定義して使用する


			XA_Play(SOUND_LABEL::S_FALL);
			player->GetPlayerAnim()->StopWalk(player->GetDirection());
			Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
			fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
			Vector3 pos = player->mTransform.pos;
			Vector3 scale = player->mTransform.scale;
			pos.z -= 0.000001f;
			scale.x *= MARK_SCALE;
			scale.y *= MARK_SCALE;
			player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::MARK, false);
			player->dotween->DelayedCall(0.5f, [&]()
				{
					XA_Play(SOUND_LABEL::S_BIKKURI);
				});
			player->dotween->DelayedCall(FALL_TIME / 2, [&]()
				{
					player->Fall();
					XA_Play(SOUND_LABEL::S_FLY_BATABATA);
				});
			player->dotween->DoDelay(FALL_TIME);
			player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);

			player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
			Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
			player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
			if (player->GetNowFloor() != 1)
			{
				if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
				{
					//バウンドする高さを計算　代入
					float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
					player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
					player->dotween->DelayedCall(FALLMOVE_TIME + FALL_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
						{
							XA_Play(SOUND_LABEL::S_TYAKUTI);
							isFallBound = true;
						});
				}
			}
			player->dotween->DelayedCall(FALLMOVE_TIME + FALLMOVE_TIME, [&]()
				{
					player->fallMoveTrriger = true;
				});
		}
		else
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
				XA_Play(SOUND_LABEL::S_CHANGE);
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
			}
			player->GetPlayerAnim()->StopWalk(player->GetDirection());
			player->ChangeTexture(Player::ANIM_TEX::WAIT);
			player->dotween->DelayedCall(0.1f, [&]()
				{
					FallAfter();
				});
		}
		break;
	}
	case CGridObject::BlockType::HOLL:
	{
		//WalkStart();
		//ジャンプしてから落ちるように

		XA_Play(SOUND_LABEL::S_FALL);
		//画面外まで移動するようにYをマクロで定義して使用する
		Vector3 fallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::FLOOR));
		fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
		Vector2 fallPosXY;
		fallPosXY.x = fallPos.x;
		fallPosXY.y = fallPos.y;
		player->Fall();
		player->dotween->DoMoveXY(fallPosXY, FALLMOVE_TIME);
		player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
		Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
		if (player->GetNowFloor() != 1)
		{
			if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
			{
				//バウンドする高さを計算　代入
				float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
				player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
				player->dotween->DelayedCall(FALLMOVE_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
					{
						XA_Play(SOUND_LABEL::S_TYAKUTI);
						isFallBound = true;
					});
			}
		}
		player->dotween->DelayedCall(FALLMOVE_TIME, [&]()
			{
				player->fallMoveTrriger = true;
			});


	}
	break;

	case CGridObject::BlockType::GUMI:
	{

		//WalkStart();
		MoveAfter();
		FallAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);

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
			XA_Play(SOUND_LABEL::S_CHANGE);
			player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
			player->Stop();
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
