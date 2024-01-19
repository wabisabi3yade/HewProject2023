#include "ThinMove.h"
#include "Player.h"

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
				// 食べ終わったら移動できるようにする
				player->dotween->DelayedCall(EAT_TIME, [&]() {player->EatCake(); MoveAfter(); });
			});
		break;

	case CGridObject::BlockType::CHILI:
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				player->dotween->DelayedCall(EAT_TIME, [&]() {player->EatChilli(); MoveAfter(); });
			});
		break;

	case CGridObject::BlockType::PROTEIN:
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
				CGrid::GRID_XY GridXY = (nextGridPos);
				float player_z = player->mTransform.pos.z;
				//画面外まで移動するようにYをマクロで定義して使用する
				GridXY.x -= 1;
				GridXY.y += 1;
				Vector3 fallPos(player->GetGridTable()->GridToWorld(GridXY, CGridObject::BlockType::FLOOR));
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
		// ↓におちるときのジャンプ

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY.x, WALK_TIME);
		//player->dotween->Join(forwardPosXY.y, WALK_TIME, DoTween::FUNC::MOVE_Y);
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
				player->dotween->Append(fallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
				switch (player->GetNowFloor())
				{
				case 1:
					break;
				case 2:
				{
					player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
					Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetGridPos(), CGridObject::BlockType::START));
					player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
				}
				break;
				case 3:
				{

					player->dotween->DoDelay(FALLMOVE_TIME);
					Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetGridPos(), CGridObject::BlockType::START));
					player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
				}
				break;
				default:
					break;
				}
			});
		break;

	case CGridObject::BlockType::GUMI:
		// ↑にジャンプする
	{
		WalkStart();

		Vector2 junpPos = {};

		Vector3 Vec3JumpPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		junpPos.x = Vec3JumpPos.x;
		junpPos.y = Vec3JumpPos.y;
		player->dotween->DoMoveCurve(junpPos, 1.5f,junpPos.y );
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]() {WalkAfter(); MoveAfter(); });

		// ↑にジャンプする
	}
		break;

	case CGridObject::BlockType::BAUMHORIZONTAL:
	case CGridObject::BlockType::BAUMVERTICAL:
	{

		// バウムクーヘンの向こう側に移動する
		// もう一個先に座標設定
		nextGridPos.x += d.x;
		nextGridPos.y += d.y;

		WalkStart();

		forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::START);
		forwardPosXY = { forwardPos.x, forwardPos.y };

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		// 動き終わったら
		player->dotween->OnComplete([&]()
			{
				WalkAfter();

				// カステラ超えた先にブロックによって処理をする
				switch (static_cast<CGridObject::BlockType>(player->GetGridTable()->CheckObjectType(nextGridPos)))
				{
				case CGridObject::BlockType::CAKE:
					// 食べ終わったら移動できるようにする
					player->dotween->DelayedCall(EAT_TIME, [&]() {player->EatCake(); MoveAfter(); });
					break;

				case CGridObject::BlockType::CHILI:
					// 食べ終わったら移動できるようにする
					player->dotween->DelayedCall(EAT_TIME, [&]() {player->EatChilli(); MoveAfter(); });
					break;

				case CGridObject::BlockType::PROTEIN:
					player->dotween->DelayedCall(EAT_TIME, [&]() { MoveAfter(); });
					break;

				case CGridObject::BlockType::COIN:

					break;

				case CGridObject::BlockType::CHOCO:

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
							player->dotween->Append(fallPos, WALK_TIME, DoTween::FUNC::MOVE_XY);
						});
					break;
				default:
					MoveAfter();
					break;
				}
			});
	}
		break;


	default:

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]() {WalkAfter(); MoveAfter(); });
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
