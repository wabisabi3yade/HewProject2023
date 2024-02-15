#include "ThinMove.h"
#include "Player.h"
#include "CBaum.h"

ThinMove::ThinMove(Player* _p)
	: PlayerMove(_p)
{
	// 移動不可能な床の種類を決める
	cantMoveBlock = { 0, 2, 5, 16 };
}

void ThinMove::Move(DIRECTION _dir)
{
	// 移動フラグをtrue
	isMoving = true;
	isMoveStartTrigger = true;

	// 方向を設定する
	player->SetDirection(static_cast<int>(_dir));

	//	移動先のグリッド座標
	nextGridPos = player->GetGridPos();
	CGrid::GRID_XY d = {};
	switch (_dir)
	{
	case DIRECTION::UP:

		d.y += -1;
		break;

	case DIRECTION::DOWN:
		d.y += 1;
		break;

	case DIRECTION::RIGHT:
		d.x += 1;
		break;

	case DIRECTION::LEFT:
		d.x += -1;
		break;
	}
	nextGridPos.x += d.x;
	nextGridPos.y += d.y;

	//	ここから移動する先の種類によってすることを変える //////////////////////////
	// キャラクターを移動先の座標
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::START);
	Vector2 forwardPosXY = { forwardPos.x, forwardPos.y };

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
				if (player->GetCalorie() <= 0)
				{
					player->GameOver();
					return;
				}
				player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				pos.z -= 0.000001f;
				pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
				scale.x *= HEART_SCALE;
				scale.y *= HEART_SCALE;
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::HEART, false);
				//煙用に
				pos = player->mTransform.pos;
				pos.z -= 0.000001f;
				pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
				scale = player->mTransform.scale;
				scale.x *= SMOKE_SCALE;
				scale.y *= SMOKE_SCALE;
				// 食べ終わったら移動できるようにする
				player->dotween->DelayedCall(EAT_TIME, [&, pos, scale]()
					{
						player->EatEnd();
						player->EatCake();
						MoveAfter();
						player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_G, false);
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
				if (player->GetCalorie() <= 0)
				{
					player->GameOver();
					return;
				}
				player->ChangeTexture(Player::ANIM_TEX::EAT_CHILI);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						player->EatEnd();
						player->EatChilli();
						MoveAfter();
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

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				WalkAfter();

				MoveAfter();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);

			});

		break;

	case CGridObject::BlockType::HOLL:
		// ↓におちるときのジャンプ

		WalkStart();
		{

			Vector2 junpPos = {};

			Vector3 Vec3JumpPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
			junpPos.x = Vec3JumpPos.x;
			junpPos.y = Vec3JumpPos.y;
			player->dotween->DoMoveCurve(junpPos, JUMP_TIME);
			player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

			player->dotween->OnComplete([&]()
				{
					//画面外まで移動するようにYをマクロで定義して使用する
					Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
					fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
					Vector2 fallPosXY;
					fallPosXY.x = fallPos.x;
					fallPosXY.y = fallPos.y;
					player->Fall();
					player->dotween->DoMoveXY(fallPosXY, FALLMOVE_TIME);
					//player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
					player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
					Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
					player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
					if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
					{
						//バウンドする高さを計算　代入
						//player->Fall();
						float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
						player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
						//player->dotween->DoMoveCurve({ floorFallPos.x,floorFallPos.y }, BOUND_TIME, BoundPosY);
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
		//MoveAfter();

		player->dotween->Append(junpPos.y - 0.3f, 0.5f, DoTween::FUNC::MOVE_Y);
		player->dotween->OnComplete([&, Vec3JumpPos]()
			{
				player->dotween->DoDelay(0.3f);
				player->dotween->Append(Vec3JumpPos.y, RISING_TIME, DoTween::FUNC::MOVE_Y);
				player->Rise();
				player->GetPlayerMove()->RiseStart();
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

	case CGridObject::BlockType::BAUMHORIZONTAL:
	case CGridObject::BlockType::BAUMVERTICAL:
	{
		CGrid::GRID_XY nextGridPosCopy = nextGridPos;
		// バウムクーヘンの向こう側に移動する
		// もう一個先に座標設定
		nextGridPosCopy.x += d.x;
		nextGridPosCopy.y += d.y;

		CGrid::GRID_XY XY = { 0,0 };
		for (int i = 0; i < 9; i++)
		{
			if (player->GetGridTable()->floorTable[0][i] != 0)
			{
				XY.x += 1;
			}
			if (player->GetGridTable()->floorTable[i][0] != 0)
			{
				XY.y += 1;
			}
			else if (player->GetGridTable()->floorTable[i][i] == 0)
			{
				break;
			}
		}
		if (nextGridPosCopy.x < 0 || nextGridPosCopy.y < 0 || nextGridPosCopy.x > XY.x || nextGridPosCopy.y > XY.y)
		{
			nextGridPos = player->GetGridPos();
			MoveAfter();
			return;
		}
		//player->ChangeTexture(Player::ANIM_TEX::BAUM);
		WalkStart();
		player->ChangeInvisible();
		forwardPos = player->GetGridTable()->GridToWorld(nextGridPosCopy, CGridObject::BlockType::START);
		forwardPosXY = { forwardPos.x, forwardPos.y };

		// プレイヤーを移動させておく
		player->mTransform.pos = forwardPos;


		Vector2 baumAdjustPos = Vector2::zero;
		// バウムクーヘン微調整座標
		switch (_dir)
		{
		case DIRECTION::DOWN:
			baumAdjustPos = { 0.015f, 0.1f };
			break;

		case DIRECTION::UP:
			baumAdjustPos = { -0.0180f, 0.058f };
			break;

		case DIRECTION::RIGHT:
			baumAdjustPos = { 0.022f,0.06f };
			break;


		case DIRECTION::LEFT:
			baumAdjustPos = { -0.013f, 0.103f };
			break;
		}
		player->mTransform.pos.x += baumAdjustPos.x * player->GetGridTable()->GetGridScale().x;
		player->mTransform.pos.y += baumAdjustPos.y * player->GetGridTable()->GetGridScale().y;

		// 動き終わったら
		player->dotween->DelayedCall(BAUM_THROWENDTIME, [&, nextGridPosCopy]()
			{
				nextGridPos = nextGridPosCopy;
				// カステラ超えた先にブロックによって処理をする
				switch (static_cast<CGridObject::BlockType>(player->GetGridTable()->CheckMassType(nextGridPosCopy)))
				{
				case CGridObject::BlockType::CAKE:
				{
					WalkAfter();
					// 食べ終わったら移動できるようにする
					if (player->GetCalorie() <= 0)
					{
						player->GameOver();
						return;
					}
					player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
					player->GetPlayerAnim()->PlayEat(player->GetDirection());
					Vector3 pos = player->mTransform.pos;
					Vector3 scale = player->mTransform.scale;
					pos.z -= 0.000001f;
					pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
					scale.x *= HEART_SCALE;
					scale.y *= HEART_SCALE;
					player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::HEART, false);
					//煙用に
					pos = player->mTransform.pos;
					pos.z -= 0.000001f;
					pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
					scale = player->mTransform.scale;
					scale.x *= SMOKE_SCALE;
					scale.y *= SMOKE_SCALE;
					// 食べ終わったら移動できるようにする
					player->dotween->DelayedCall(EAT_TIME, [&, pos, scale]()
						{
							player->EatEnd();
							player->EatCake();
							MoveAfter();
							player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_G, false);
							player->GetPlayerAnim()->StopWalk(player->GetDirection());
							player->ChangeTexture(Player::ANIM_TEX::WAIT);
						});
					break;
				}
				case CGridObject::BlockType::CHILI:
					WalkAfter();
					// 食べ終わったら移動できるようにする
					if (player->GetCalorie() <= 0)
					{
						player->GameOver();
						return;
					}
					player->ChangeTexture(Player::ANIM_TEX::EAT_CHILI);
					player->GetPlayerAnim()->PlayEat(player->GetDirection());
					player->dotween->DelayedCall(EAT_TIME, [&]()
						{
							player->EatEnd();
							player->EatChilli();
							MoveAfter();
							player->GetPlayerAnim()->StopWalk(player->GetDirection());
							player->ChangeTexture(Player::ANIM_TEX::WAIT);
						});
					break;
				case CGridObject::BlockType::PROTEIN:
					WalkAfter();
					nextGridPos = nextGridPosCopy;
					player->dotween->DelayedCall(EAT_TIME, [&]()
						{
							MoveAfter();
							player->GetPlayerAnim()->StopWalk(player->GetDirection());
							player->ChangeTexture(Player::ANIM_TEX::WAIT);
						});
					break;

				case CGridObject::BlockType::COIN:
					WalkAfter();
					nextGridPos = nextGridPosCopy;
					MoveAfter();
					player->GetPlayerAnim()->StopWalk(player->GetDirection());
					player->ChangeTexture(Player::ANIM_TEX::WAIT);
					break;

				case CGridObject::BlockType::CHOCO:
					WalkAfter();
					nextGridPos = nextGridPosCopy;
					MoveAfter();
					player->GetPlayerAnim()->StopWalk(player->GetDirection());
					player->ChangeTexture(Player::ANIM_TEX::WAIT);
					break;

				case CGridObject::BlockType::CHOCOCRACK:
					WalkAfter();
					nextGridPos = nextGridPosCopy;
					MoveAfter();
					player->GetPlayerAnim()->StopWalk(player->GetDirection());
					player->ChangeTexture(Player::ANIM_TEX::WAIT);
					break;

				case CGridObject::BlockType::HOLL:
				{
					Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
					fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
					Vector2 fallPosXY;
					fallPosXY.x = fallPos.x;
					fallPosXY.y = fallPos.y;
					player->ChangeTexture(Player::ANIM_TEX::WAIT);
					player->dotween->DelayedCall(FALL_TIME / 2, [&]()
						{
							player->Fall();
							player->ChangeTexture(Player::ANIM_TEX::WALK);
						});
					player->dotween->DoDelay(FALL_TIME);
					player->dotween->Append(fallPos, WALK_TIME, DoTween::FUNC::MOVE_XY);

					player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
					Vector3 floorFallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::START));
					player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
					if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
					{
						//バウンドする高さを計算　代入
						float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
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
					break;
				}
				default:
					WalkAfter();
					nextGridPos = nextGridPosCopy;
					MoveAfter();
					break;
				}
			});
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
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME, junpPos.y + (CANNON_IN_CURVE_POS_Y * player->GetGridTable()->GetGridScale().y));
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				player->SetGridPos(nextGridPos);
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				player->GetPlayerMove()->InCannon();
			});
	}
	break;

	default:

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				MoveAfter();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
			});
		break;
	}
}

void ThinMove::Step()
{
	switch (player->GetPlayerMove()->CheckNextMassType())
	{
	case CGridObject::BlockType::CAKE:

		player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
		player->GetPlayerAnim()->PlayEat(player->GetDirection());
		// 食べ終わったら移動できるようにする
		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
				player->EatEnd();
				player->EatCake();
				MoveAfter();
				FallAfter();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
			});
		break;

	case CGridObject::BlockType::CHILI:
		player->ChangeTexture(Player::ANIM_TEX::EAT_CHILI);
		player->GetPlayerAnim()->PlayEat(player->GetDirection());
		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
				player->EatChilli();
				player->EatEnd();
				MoveAfter();
				FallAfter();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
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
	case CGridObject::BlockType::HOLL:
	{
		WalkStart();
		//画面外まで移動するようにYをマクロで定義して使用する
		Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
		fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
		Vector2 fallPosXY;
		fallPosXY.x = fallPos.x;
		fallPosXY.y = fallPos.y;
		player->Fall();
		player->dotween->DoMoveXY(fallPosXY, FALLMOVE_TIME);
		//player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
		player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
		Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
		if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
		{
			//バウンドする高さを計算　代入
			//player->Fall();
			float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
			player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
			//player->dotween->DoMoveCurve({ floorFallPos.x,floorFallPos.y }, BOUND_TIME, BoundPosY);
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
		FallAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		break;
	}
}

void ThinMove::CheckCanMove()
{
	// 全ての方向をtrue
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}

	// 後ろの方向に行けないようにする
	switch (static_cast<Player::DIRECTION>(player->GetDirection()))
	{
	case Player::DIRECTION::UP:
		canMoveDir[static_cast<int>(DIRECTION::DOWN)] = false;
		break;

	case Player::DIRECTION::DOWN:
		canMoveDir[static_cast<int>(DIRECTION::UP)] = false;
		break;

	case Player::DIRECTION::RIGHT:
		canMoveDir[static_cast<int>(DIRECTION::LEFT)] = false;
		break;

	case Player::DIRECTION::LEFT:
		canMoveDir[static_cast<int>(DIRECTION::RIGHT)] = false;
		break;
	}


	//↓進路先の床の情報で移動できるか判断する //////////////////////////
	// 4方向見る
	for (int dirRoop = 0; dirRoop < static_cast<int>(Player::DIRECTION::NUM); dirRoop++)
	{
		// 後ろ以外を見るだけで大丈夫なので
		if (!canMoveDir[dirRoop]) continue;

		// 方向
		CGrid::GRID_XY d = {};

		switch (static_cast<DIRECTION>(dirRoop))
		{
		case DIRECTION::UP:
			d.y = -1;
			break;

		case DIRECTION::DOWN:
			d.y = 1;
			break;

		case DIRECTION::RIGHT:
			d.x = 1;
			break;

		case DIRECTION::LEFT:
			d.x = -1;
			break;
		}
		// プレイヤーの進行先のグリッド座標を取得
		CGrid::GRID_XY forwordPos = player->GetGridPos();
		forwordPos.x += d.x;
		forwordPos.y += d.y;

		// 移動先がマップ外なら移動できないようにする
		if (forwordPos.x < 0 || forwordPos.y < 0
			|| player->GetGridTable()->floorTable[forwordPos.y][forwordPos.x] == 0)
		{
			canMoveDir[dirRoop] = false;
			continue;
		}

		// その方向に移動不可のブロックなら
		for (int j = 0; j < cantMoveBlock.size(); j++)
		{
			// 進路先が移動できないなら
			if (player->GetGridTable()->objectTable[forwordPos.y][forwordPos.x] == cantMoveBlock[j] ||
				player->GetGridTable()->floorTable[forwordPos.y][forwordPos.x] == cantMoveBlock[j])
			{
				canMoveDir[dirRoop] = false;
				break;
			}
		}
		if (!canMoveDir[dirRoop]) continue;	// ここまでで通れないことが決まっていたら次の方向を確認

		// バウムクーヘンの方向で行けるか確認する
		// 移動先が横向きバウム　かつ　移動方向が縦なら
		if (player->GetGridTable()->CheckObjectType(forwordPos) ==
			static_cast<int>(CGridObject::BlockType::BAUMHORIZONTAL) &&
			d.y != 0)
		{
			canMoveDir[dirRoop] = false;
			continue;
		}
		// 移動先が縦向きバウム　かつ　移動方向が横なら
		else if (player->GetGridTable()->CheckObjectType(forwordPos) ==
			static_cast<int>(CGridObject::BlockType::BAUMVERTICAL) &&
			d.x != 0)
		{
			canMoveDir[dirRoop] = false;
			continue;
		}
	}
}

ThinMove::~ThinMove()
{
}
