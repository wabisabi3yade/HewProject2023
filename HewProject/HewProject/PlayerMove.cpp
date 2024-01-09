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

	// ��������
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
	// �ړ����Ă���Ƃ��͏������Ȃ�
	if (isMoving) return;

	// ���͂�����
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		// ���̕����Ɉړ��ł���Ȃ�
		if (!canMoveDir[static_cast<int>(DIRECTION::RIGHT)]) return;
		player->SetDirection(static_cast<int>(DIRECTION::RIGHT));
		// �ړ�����
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
	// �ړ����I�����t���O��true
	isWalkEnd = true;
}

CStageMake::BlockType PlayerMove::CheckNextMassType()
{
	// ��ɃI�u�W�F�N�g�̌^������
	CStageMake::BlockType type = CheckNextObjectType();

	// �����Ȃ�������
	if (type == CStageMake::BlockType::NONE)
	{
		// ���̃e�[�u�����m�F
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
	// �S�Ă̕�����true
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}

	// ���̕����ɍs���Ȃ��悤�ɂ���
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


	//���i�H��̏��̏��ňړ��ł��邩���f���� //////////////////////////
	// 4��������
	for (int dirRoop = 0; dirRoop < static_cast<int>(Player::DIRECTION::NUM); dirRoop++)
	{
		// ���ȊO�����邾���ő��v�Ȃ̂�
		if (!canMoveDir[dirRoop]) continue;

		// ����
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


		// �v���C���[�̐i�s��̃O���b�h���W���擾
		CGrid::GRID_XY forwordPos = player->GetGridPos();
		forwordPos.x += d.x;
		forwordPos.y += d.y;

		// �ړ��悪�}�b�v�O�Ȃ�ړ��ł��Ȃ��悤�ɂ���
		if (forwordPos.x < 0 || forwordPos.y < 0
			|| player->GetGridTable()->floorTable[forwordPos.y][forwordPos.x] == 0)
		{
			canMoveDir[dirRoop] = false;
			continue;
		}

		for (int j = 0; j < cantMoveBlock.size(); j++)
		{
			// �i�H�悪�ړ��ł��Ȃ��Ȃ�
			if (player->GetGridTable()->floorTable[forwordPos.y][forwordPos.x] == cantMoveBlock[j] ||
				player->GetGridTable()->objectTable[forwordPos.y][forwordPos.x] == cantMoveBlock[j])
			{
				canMoveDir[dirRoop] = false;
				break;
			}
		}
	}
	//���i�H��̏��̏��ňړ��ł��邩���f���� //////////////////////////
}

void PlayerMove::MoveAfter()
{
	// �ړ��t���O��߂�
	isMoving = false;
	isMovingTrigger = true;

	// �������ŃO���b�h���W���Z�b�g���Ă���
	player->SetGridPos(nextGridPos.x, nextGridPos.y);

	// �ړ��ł�����������肷��
	CheckCanMove();

	// �}�b�`������Ȃ��Ȃ�
	if (player->GetState() == Player::STATE::MUSCLE) return;
	// �����I�������ƂɃJ�����[����ԕς��悤�Ȃ��Ԃ�ω�������
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
