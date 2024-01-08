#include "FatMove.h"
#include "Player.h"
#include "CCastella.h"

FatMove::FatMove(Player* _p)
	: PlayerMove(_p)
{
	// �ړ��s�\�ȏ��̎�ނ����߂�
	cantMoveBlock = { 0, 2, 6, 7, 16 };
}

void FatMove::Move(DIRECTION _dir)
{
	// �ړ��t���O��true
	isMoving = true;
	isMoveStartTrigger = true;

	// ������ݒ肷��
	player->SetDirection(static_cast<int>(_dir));

	//	�ړ���̃O���b�h���W
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

	//	��������ړ������̎�ނɂ���Ă��邱�Ƃ�ς��� //////////////////////////
	// �L�����N�^�[���ړ���̍��W
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CStageMake::BlockType::START);

	// �i�񂾐�̃u���b�N�ɂ���đΉ�����A�N�V������ݒ肷��
	switch (CheckNextObjectType())
	{
	case CStageMake::BlockType::CAKE:
		// �ړ�����
		player->dotween->DoMove(forwardPos, WALK_TIME);
		// �ړ����I������P�[�L��H�ׂ�
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				// �H�׏I�������ړ��ł���悤�ɂ���
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
		// �J�X�e����������ƈړ��ł���悤�ɂ���
		player->dotween->DoMove(forwardPos, CASTELLAWALK_TIME);
		// �ړ��I���̑ҋ@����
		{
			float waitTime = 0;

			// �J�X�e���̈ړ���Ɍ�������Ȃ�
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
		// ���ɂ�����Ƃ��̃W�����v

		break;

	case CStageMake::BlockType::GUMI:
		// ���ɃW�����v����

		break;

	default:
		player->dotween->DoMove(forwardPos, WALK_TIME);
		player->dotween->OnComplete([&]() {WalkAfter(); MoveAfter(); });
		break;
	}
}

void FatMove::CheckCanMove()
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

		// ���̕����Ɉړ��s�̃u���b�N�Ȃ�
		for (int j = 0; j < cantMoveBlock.size(); j++)
		{
			// �i�H�悪�ړ��ł��Ȃ��Ȃ�
			if (player->GetGridTable()->objectTable[forwordPos.y][forwordPos.x] == cantMoveBlock[j] ||
				player->GetGridTable()->floorTable[forwordPos.y][forwordPos.x] == cantMoveBlock[j])
			{
				canMoveDir[dirRoop] = false;
				break;
			}
		}
		if (!canMoveDir[dirRoop]) continue;	// �����܂łŒʂ�Ȃ����Ƃ����܂��Ă����玟�̕������m�F

		// �ړ���ɃJ�X�e��������Ȃ�
		if (player->GetGridTable()->CheckObjectType(forwordPos) ==
			static_cast<int>(CStageMake::BlockType::CASTELLA))
		{
			// �ړ���̃J�X�e���̍��W
			CGrid::GRID_XY nextCastella = forwordPos;
			nextCastella.x += d.x;
			nextCastella.y += d.y;

			// �J�X�e���ړ���ɂ���炪����Ȃ�
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
			// �J�X�e���ړ��悪�}�b�v�O�Ȃ�
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
