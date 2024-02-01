#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "PlayerMove.h"
#include "CInput.h"
#include "Player.h"

PlayerMove::PlayerMove(Player* _p)
{
	player = _p;

	// ��������
	for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
	{
		canMoveDir[i] = false;
		cannonMoveDir[i] = false;
	}
	isMovingTrigger = false;
	isMoving = false;
	isWalkEnd = false;
	isMoveStartTrigger = false;
	isWalking_now = false;
	isWalking_old = false;
	isFalling = false;
	isRising = false;
	isCannonMove = false;
	isCannonMoveEnd = false;
	isCannonMoveStart = false;
	inCannon = false;
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
		if (inCannon == false)
		{
			// �ړ�����
			Move(DIRECTION::RIGHT);
		}
		else
		{
			CannonDirSelect(DIRECTION::RIGHT);
		}
	}
	else if (gInput->GetKeyTrigger(VK_LEFT))
	{
		if (!canMoveDir[static_cast<int>(DIRECTION::LEFT)]) return;
		player->SetDirection(static_cast<int>(DIRECTION::LEFT));
		if (inCannon == false)
			Move(DIRECTION::LEFT);
		else
			CannonDirSelect(DIRECTION::LEFT);
	}
	else if (gInput->GetKeyTrigger(VK_UP))
	{
		if (!canMoveDir[static_cast<int>(DIRECTION::UP)]) return;
		player->SetDirection(static_cast<int>(DIRECTION::UP));
		if (inCannon == false)
			Move(DIRECTION::UP);
		else
			CannonDirSelect(DIRECTION::UP);
	}
	else if (gInput->GetKeyTrigger(VK_DOWN))
	{
		if (!canMoveDir[static_cast<int>(DIRECTION::DOWN)]) return;
		player->SetDirection(static_cast<int>(DIRECTION::DOWN));
		if (inCannon == false)
			Move(DIRECTION::DOWN);
		else
			CannonDirSelect(DIRECTION::DOWN);
	}
	else if (gInput->GetKeyTrigger(VK_ESCAPE))
	{
		isCannonMove = !isCannonMove;
	}
	else if (gInput->GetKeyTrigger(VK_SPACE))
	{
		InCannon();
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
	if(!inCannon)
	player->WalkCalorie();

	isWalking_now = false;
	isWalking_old = true;
	// �ړ����I�����t���O��true
	isWalkEnd = true;
}

CGridObject::BlockType PlayerMove::CheckNextMassType()
{
	// ��ɃI�u�W�F�N�g�̌^������
	CGridObject::BlockType type = CheckNextObjectType();

	// �����Ȃ�������
	if (type == CGridObject::BlockType::NONE)
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

CGridObject::BlockType PlayerMove::CheckNextObjectType()
{
	return static_cast<CGridObject::BlockType>(player->GetGridTable()->objectTable[nextGridPos.y][nextGridPos.x]);
}

void PlayerMove::FallStart()
{
	isFalling = true;
}

void PlayerMove::RiseStart()
{
	isRising = true;
}

CGridObject::BlockType PlayerMove::CheckNextFloorType()
{
	return static_cast<CGridObject::BlockType>(player->GetGridTable()->floorTable[nextGridPos.y][nextGridPos.x]);
}

CGridObject::BlockType PlayerMove::CheckNowFloorType()
{
	CGrid::GRID_XY NowGridPos = player->GetGridPos();
	return static_cast<CGridObject::BlockType>(player->GetGridTable()->floorTable[NowGridPos.y][NowGridPos.x]);
}

CGridObject::BlockType PlayerMove::CheckNowObjectType()
{
	CGrid::GRID_XY NowGridPos = player->GetGridPos();
	return static_cast<CGridObject::BlockType>(player->GetGridTable()->objectTable[NowGridPos.y][NowGridPos.x]);
}

CGridObject::BlockType PlayerMove::CheckNowMassType()
{
	// ��ɃI�u�W�F�N�g�̌^������
	CGridObject::BlockType type = CheckNowObjectType();

	// �����Ȃ�������
	if (type == CGridObject::BlockType::NONE || type == CGridObject::BlockType::START)
	{
		// ���̃e�[�u�����m�F
		type = CheckNowFloorType();
	}
	return type;
}

void PlayerMove::FallAfter()
{
	isFalling = false;
}

void PlayerMove::RiseAfter()
{
	isRising = false;
}

void PlayerMove::InCannon()
{
	inCannon = true;
}

void PlayerMove::CannonMove1()
{
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

	CGrid::GRID_XY movePos = player->GetGridPos();
	int moveDir = 0;
	cannonMoveDir[static_cast<int>(DIRECTION::UP)] = true;
	for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
	{
		if (cannonMoveDir[i] == true)
		{
			moveDir = i;
			break;
		}
	}


	switch (moveDir)
	{
	case static_cast<int>(DIRECTION::DOWN):
		for (int i = player->GetGridPos().y; i < XY.y; i++)
		{
			if (player->GetGridTable()->objectTable[i - 1][player->GetGridPos().x] != static_cast<int>(CGridObject::BlockType::GALL))
			{
				movePos.y++;
			}
			else
			{
				break;
			}
		}
		break;
	case static_cast<int>(DIRECTION::UP):
		for (int i = player->GetGridPos().y; i > 0; i--)
		{
			if (player->GetGridTable()->objectTable[i - 1][player->GetGridPos().x] != static_cast<int>(CGridObject::BlockType::GALL))
			{
				movePos.y--;
			}
			else
			{
				break;
			}
		}
		break;
	case static_cast<int>(DIRECTION::RIGHT):
		for (int i = player->GetGridPos().x; i < XY.x; i++)
		{
			if (player->GetGridTable()->objectTable[player->GetGridPos().y][i - 1] != static_cast<int>(CGridObject::BlockType::GALL))
			{
				movePos.x++;
			}
			else
			{
				break;
			}
		}
		break;
	case static_cast<int>(DIRECTION::LEFT):
		for (int i = player->GetGridPos().x; i > 0; i--)
		{
			if (player->GetGridTable()->objectTable[player->GetGridPos().y][i - 1] != static_cast<int>(CGridObject::BlockType::GALL))
			{
				movePos.x--;
			}
			else
			{
				break;
			}
		}
		break;
	default:
		break;
	}

	WalkStart();
	Vector3 v3MovePos = player->GetGridTable()->GridToWorld(movePos, CGridObject::BlockType::START);
	//�ړ��ʂɉ����đ��x��ς���
	player->dotween->DoMoveXY({ v3MovePos.x,v3MovePos.y }, CANNONMOVE_TIME / ((movePos.x - player->GetGridPos().x) + (movePos.y + player->GetGridPos().y)));
	player->dotween->OnComplete([&, movePos, v3MovePos]()
		{
			player->dotween->DoMoveCurve({ player->mTransform.pos.x,player->mTransform.pos.y }, CANNONBOUND_TIME, player->mTransform.pos.y + CANNONBOUND_POS_Y);
			//����ύX����
			player->dotween->Append(v3MovePos, 0.0f, DoTween::FUNC::MOVE_Z);
			player->dotween->DelayedCall(CANNONBOUND_TIME, [&, movePos]()
				{
					//WalkAfter();
					player->SetGridPos(movePos);
					player->GetPlayerMove()->SetNextGridPos(movePos);
					MoveAfter();
					Step();
				});
		});
}

void PlayerMove::CannonMove2()
{
	if (isCannonMoveStart)
	{
		return;
	}
	int moveDir = 0;
	bool isBound = false;
	CGrid::GRID_XY movePos = player->GetGridPos();
	//cannonMoveDir[static_cast<int>(DIRECTION::UP)] = true;
	for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
	{
		if (cannonMoveDir[i] == true)
		{
			moveDir = i;
			break;
		}
	}
	if (player->GetCangeCannonTexture() == false)
	{
		player->ChangeTexture(Player::ANIM_TEX::CANNON);
		player->SetChangeCannonTexture(true);
		dynamic_cast<CPlayerAnim*>(player->GetmAnim())->PlayCannon(moveDir, 3.0f);
		nextCannonPos = movePos;
	}
	
	if (!isCannonMoveStart )
	{
		switch (moveDir)
		{
		case static_cast<int>(DIRECTION::DOWN):
			movePos.y++;
			movePos.y++;
			nextCannonPos.y++;
			nextGridPos = nextCannonPos;
			break;

		case static_cast<int>(DIRECTION::UP):
			movePos.y--;
			movePos.y--;
			nextCannonPos.y--;
			nextGridPos = nextCannonPos;
			break;

		case static_cast<int>(DIRECTION::RIGHT):
			movePos.x++;
			movePos.x++;
			nextCannonPos.x++;
			nextGridPos = nextCannonPos;
			break;

		case static_cast<int>(DIRECTION::LEFT):
			movePos.x--;
			movePos.x--;
			nextCannonPos.x--;
			nextGridPos = nextCannonPos;
			break;
		default:
			break;
		}

	}
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
	CGrid::GRID_XY a = nextCannonPos;
	if (nextCannonPos.x >= 0.0f && nextCannonPos.y >= 0.0f &&
		player->GetGridTable()->objectTable[nextCannonPos.y][nextCannonPos.x] != 0
		&& nextCannonPos.x < XY.x && nextCannonPos.y < XY.y)
	{
		if (player->GetGridTable()->objectTable[nextCannonPos.y][nextCannonPos.x] != static_cast<int> (CGridObject::BlockType::GALL))
		{
			WalkAfter();
			Vector3 v3MovePos = player->GetGridTable()->GridToWorld(nextCannonPos, CGridObject::BlockType::START);
			isCannonMoveStart = true;
			player->dotween->DoMoveXY({ v3MovePos.x,v3MovePos.y }, CANNONMOVE_TIME);
			player->dotween->Append(v3MovePos, 0.0f, DoTween::FUNC::MOVE_Z);
			player->dotween->OnComplete([&, v3MovePos, movePos, moveDir, XY,a]()
				{
					if (player->GetGridTable()->CheckObjectType(nextCannonPos) == static_cast<int>(CGridObject::BlockType::CAKE))
					{
						kari = true;
						//player->EatCake();
						//player->SetChangeCannonTexture(false);
						player->ChangeTexture(Player::ANIM_TEX::CANNON);
						player->SetChangeCannonTexture(true);
						dynamic_cast<CPlayerAnim*>(player->GetmAnim())->PlayCannon(moveDir, 3.0f);
					}
					
					//if (player->GetGridTable()->CheckObjectType(a) == static_cast<int>(CGridObject::BlockType::CAKE))
					//{
					//	
					//}


					// �ړ�������̏������̃I�u�W�F�N�g�m�F
					if (player->GetGridTable()->objectTable[movePos.y][movePos.x] == static_cast<int>(CGridObject::BlockType::GALL) ||
						movePos.x == -1 || movePos.y == -1 || movePos.x == XY.x || movePos.y == XY.y)
					{
						player->ChangeTexture(Player::ANIM_TEX::WALK);
						dynamic_cast<CPlayerAnim*>(player->GetmAnim())->PlayFall(moveDir, 2.0f);
						//dynamic_cast<CPlayerAnim*>(player->GetmAnim())->animSpeed=1.0f;
						player->dotween->DoMoveCurve({ v3MovePos.x,v3MovePos.y }, CANNONBOUND_TIME, v3MovePos.y + CANNONBOUND_POS_Y);
						player->dotween->DelayedCall(CANNONBOUND_TIME, [&,movePos,a]()
							{
								//player->SetGridPos(nextGridPos);
								isCannonMoveStart = false;
								isCannonMove = false;
								this->CheckCanMove();
								player->SetChangeCannonTexture(false);
								player->ChangeTexture(Player::ANIM_TEX::WAIT);
								dynamic_cast<CPlayerAnim*>(player->GetmAnim())->SetAnimSpeedRate(0.3f);
								inCannon = false;
								isCannonMoveEnd = true;
								//player->SetGridPos(Next);
								player->GetPlayerMove()->Step();
								if (kari)
								{
									player->EatCake();
								}
							});

					}
					else
					{
						WalkAfter();

						MoveAfter();
					isCannonMoveEnd = true;
					isCannonMoveStart = false;
					}
				});
		}
		//�ړ��\�ŋ�����΃o�E���h�����s����
		//��C�ړ��t���O������

	}

}

void PlayerMove::CannonDirSelect(DIRECTION _dir)
{
	for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
	{
			cannonMoveDir[i] = false;
	}

	cannonMoveDir[static_cast<int>(_dir)] = true;
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

		if (player->GetGridTable()->floorTable[forwordPos.y][forwordPos.x] == static_cast<short> (CGridObject::BlockType::HOLL) &&
			player->GetNowFloor() == 1)
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

}
