#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "PlayerMove.h"
#include "CInput.h"
#include "Player.h"
#include "CStageMake.h"

PlayerMove::PlayerMove(Player* _p)
{
	player = _p;

	// ↓初期化
	for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
	{
		canMoveDir[i] = false;
	}
	isMovingTrigger = false;
	isMoving = false;
	isWalkEnd = false;
	isMoveStartTrigger = false;
	isWalking_now = false;
	isWalking_old = false;
}

PlayerMove::~PlayerMove()
{
	cantMoveBlock.clear();
}

void PlayerMove::Input()
{
	// 移動しているときは処理しない
	if (isMoving) return;

	// 入力されると
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		// その方向に移動できるなら
		if (!canMoveDir[static_cast<int>(DIRECTION::RIGHT)]) return;
		player->SetDirection(static_cast<int>(DIRECTION::RIGHT));
		// 移動する
		Move(DIRECTION::RIGHT);
	}
	else if (gInput->GetKeyTrigger(VK_LEFT))
	{
		if (!canMoveDir[static_cast<int>(DIRECTION::LEFT)]) return;
		player->SetDirection(static_cast<int>(DIRECTION::LEFT));
		Move(DIRECTION::LEFT);

	}
	else if (gInput->GetKeyTrigger(VK_UP))
	{
		if (!canMoveDir[static_cast<int>(DIRECTION::UP)]) return;
		player->SetDirection(static_cast<int>(DIRECTION::UP));

		Move(DIRECTION::UP);

	}
	else if (gInput->GetKeyTrigger(VK_DOWN))
	{
		if (!canMoveDir[static_cast<int>(DIRECTION::DOWN)]) return;
		player->SetDirection(static_cast<int>(DIRECTION::DOWN));
		Move(DIRECTION::DOWN);
	}
}

void PlayerMove::FlagInit()
{
	isMovingTrigger = false;
	isWalkEnd = false;
	isMoveStartTrigger = false;
	isWalking_old = isWalking_now;
}

void PlayerMove::WalkAfter()
{
	player->WalkCalorie();

	isWalking_now = false;
	isWalking_old = true;
	// 移動し終えたフラグをtrue
	isWalkEnd = true;
}

CStageMake::BlockType PlayerMove::CheckNextMassType()
{
	// 先にオブジェクトの型を見る
	CStageMake::BlockType type = CheckNextObjectType();

	// 何もなかったら
	if (type == CStageMake::BlockType::NONE)
	{
		// 床のテーブルを確認
		type = CheckNextFloorType();
	}
	return type;
}

void PlayerMove::WalkStart()
{
	isWalking_now = true;
}

CStageMake::BlockType PlayerMove::CheckNextObjectType()
{
	return static_cast<CStageMake::BlockType>(player->GetGridTable()->objectTable[nextGridPos.y][nextGridPos.x]);
}

CStageMake::BlockType PlayerMove::CheckNextFloorType()
{
	return static_cast<CStageMake::BlockType>(player->GetGridTable()->floorTable[nextGridPos.y][nextGridPos.x]);
}

CStageMake::BlockType PlayerMove::CheckNowFloorType()
{
	CGrid::GRID_XY NowGridPos = player->GetGridPos();
	return static_cast<CStageMake::BlockType>(player->GetGridTable()->floorTable[NowGridPos.y][NowGridPos.x]);
}

void PlayerMove::CheckCanMove()
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

		for (int j = 0; j < cantMoveBlock.size(); j++)
		{
			// 進路先が移動できないなら
			if (player->GetGridTable()->floorTable[forwordPos.y][forwordPos.x] == cantMoveBlock[j] ||
				player->GetGridTable()->objectTable[forwordPos.y][forwordPos.x] == cantMoveBlock[j])
			{
				canMoveDir[dirRoop] = false;
				break;
			}
		}
	}
	//↑進路先の床の情報で移動できるか判断する //////////////////////////
}

void PlayerMove::MoveAfter()
{
	// 移動フラグを戻す
	isMoving = false;
	isMovingTrigger = true;

	// ↓ここでグリッド座標をセットしている
	player->SetGridPos(nextGridPos.x, nextGridPos.y);

	// 移動できる方向を決定する
	CheckCanMove();

	// マッチョじゃないなら
	if (player->GetState() == Player::STATE::MUSCLE) return;
	// 動き終えたあとにカロリーが状態変わるようなら状態を変化させる
	Player::STATE nextState = Player::STATE::FAT;
	if (player->GetCalorie() <= THIN_CALOMAX)
	{
		nextState = Player::STATE::THIN;
	}
	else if (player->GetCalorie() <= NORMAL_CALOMAX)
	{
		nextState = Player::STATE::NORMAL;
	}

	if (player->GetState() != nextState)
		player->ChangeState(nextState);
}
