#include "FatMove.h"
#include "Player.h"
#include "CCastella.h"

FatMove::FatMove(Player* _p)
	: PlayerMove(_p)
{
	// 移動不可能な床の種類を決める
	cantMoveBlock = { 0, 2, 6, 7, 16 };
}

void FatMove::Move(DIRECTION _dir)
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
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CStageMake::BlockType::START);

	// 進んだ先のブロックによって対応するアクションを設定する
	switch (CheckNextObjectType())
	{
	case CStageMake::BlockType::CAKE:
		// 移動する
		player->dotween->DoMove(forwardPos, WALK_TIME);
		// 移動し終えたらケーキを食べる
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				// 食べ終わったら移動できるようにする
				player->dotween->DelayedCall(EAT_TIME, [&]() {player->EatCake(); MoveAfter(); });
			});
		break;

	case CStageMake::BlockType::CHILI:
		player->dotween->DoMove(forwardPos, WALK_TIME);
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				player->dotween->DelayedCall(EAT_TIME, [&]() {player->EatChilli(); MoveAfter(); });
			});
		break;

	case CStageMake::BlockType::CASTELLA:
		// カステラが落ちると移動できるようにする
		player->dotween->DoMove(forwardPos, CASTELLAWALK_TIME);
		// 移動終わりの待機時間
		{
			float waitTime = 0;

			// カステラの移動先に穴があるなら
			if (player->GetGridTable()->CheckFloorType({ nextGridPos.x + d.x, nextGridPos.y + d.y }) ==
				static_cast<int>(CStageMake::BlockType::HOLL))
			{
				waitTime = CASTELLAFALL_TIME;
			}

			player->dotween->OnComplete([&]()
				{
					player->dotween->DelayedCall(waitTime, [&]() { WalkAfter(); MoveAfter(); });
				});
		}

		break;

	case CStageMake::BlockType::HOLL:
		// ↓におちるときのジャンプ

		break;

	case CStageMake::BlockType::GUMI:
		// ↑にジャンプする

		break;

	default:
		player->dotween->DoMove(forwardPos, WALK_TIME);
		player->dotween->OnComplete([&]() {WalkAfter(); MoveAfter(); });
		break;
	}
}

void FatMove::CheckCanMove()
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

		// 移動先にカステラがあるなら
		if (player->GetGridTable()->CheckObjectType(forwordPos) ==
			static_cast<int>(CStageMake::BlockType::CASTELLA))
		{
			// 移動先のカステラの座標
			CGrid::GRID_XY nextCastella = forwordPos;
			nextCastella.x += d.x;
			nextCastella.y += d.y;

			// カステラ移動先にこれらがあるなら
			switch (static_cast<CStageMake::BlockType>
				(player->GetGridTable()->CheckObjectType(nextCastella)))
			{
			case CStageMake::BlockType::WALL:
			case CStageMake::BlockType::CAKE:
			case CStageMake::BlockType::CHILI:
			case CStageMake::BlockType::COIN:
			case CStageMake::BlockType::PROTEIN:
			case CStageMake::BlockType::GALL:
			case CStageMake::BlockType::GUMI:
			case CStageMake::BlockType::BAUMHORIZONTAL:
			case CStageMake::BlockType::BAUMVERTICAL:

				canMoveDir[dirRoop] = false;
				continue;
			}
			// カステラ移動先がマップ外なら
			if (player->GetGridTable()->CheckObjectType(nextCastella) == 0 || 
				nextCastella.x < 0 || nextCastella.y < 0)
			{
				canMoveDir[dirRoop] = false;
				continue;
			}
		}
	}
}

FatMove::~FatMove()
{
}
