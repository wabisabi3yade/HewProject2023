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
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::START);
	Vector2 forwardPosXY = { forwardPos.x, forwardPos.y };

	// �����ɍs���Ƃ��̍s���̏���
	// �@ ISOME_BACKMOVE�����@�i��������́��ɂ���I�u�W�F�N�g��艜�Ɉړ�����̂ŃI�u�W�F�N�g��艜�ɂ���j
	// �A�ړ���ɓ�������Ƃ��̏��ɍ��킹��Z���W�ɍ��킹��
	if (_dir == DIRECTION::UP || _dir == DIRECTION::RIGHT)
	{
		player->mTransform.pos.z += ISOME_BACKMOVE;
	}
	// ��O�̃}�X�ɍs���Ƃ��͐��Z���W����O�ɍ��킹��
	else
	{
		player->mTransform.pos.z = forwardPos.z;
	}

	// �i�񂾐�̃u���b�N�ɂ���đΉ�����A�N�V������ݒ肷��
	switch (CheckNextMassType())
	{
	case CGridObject::BlockType::CAKE:

		WalkStart();

		// �ړ�����
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		// �ړ����I������P�[�L��H�ׂ�
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				// �H�׏I�������ړ��ł���悤�ɂ���
				player->dotween->DelayedCall(EAT_TIME, [&]() {player->EatCake(); MoveAfter(); });
			});
		break;

	case CGridObject::BlockType::CHILI:

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				player->dotween->DelayedCall(EAT_TIME, [&]() {player->EatChilli(); MoveAfter(); });
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

	case CGridObject::BlockType::CASTELLA:

		WalkStart();

		// �J�X�e����������ƈړ��ł���悤�ɂ���
		player->dotween->DoMoveXY(forwardPosXY, CASTELLAWALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		// �J�X�e���̈ړ���Ɍ�������Ȃ�
		if (player->GetGridTable()->CheckFloorType({ nextGridPos.x + d.x, nextGridPos.y + d.y }) ==
			static_cast<int>(CGridObject::BlockType::HOLL))
		{

			player->dotween->OnComplete([&]()
				{
					WalkAfter();
					player->dotween->DelayedCall(CASTELLAFALL_TIME, [&]()
						{
							MoveAfter();
						});
				});
		}
		else
		{
			player->dotween->OnComplete([&]()
				{
					WalkAfter();
					MoveAfter();
				});
		}

		break;

	case CGridObject::BlockType::CHOCO:
	case CGridObject::BlockType::CHOCOCRACK:

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				//��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����
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
	case CGridObject::BlockType::HOLL:
	{


		// ���ɂ�����Ƃ��̃W�����v

		WalkStart();


		Vector2 junpPos = {};

		Vector3 Vec3JumpPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		junpPos.x = Vec3JumpPos.x;
		junpPos.y = Vec3JumpPos.y;
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{


				//WalkAfter();
				//��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����
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
				{
					player->dotween->Append(Vector3::zero, 1.5f, DoTween::FUNC::DELAY);
					Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
					player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
					//�o�E���h���鍂�����v�Z�@���
					float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
					player->dotween->Append(floorFallPos, 1.0f, DoTween::FUNC::MOVECURVE, BoundPosY);
				}
				case 3:
				{

					//player->dotween->DoDelay(FALLMOVE_TIME);
					//Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
					//player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
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
		player->dotween->OnComplete([&, Vec3JumpPos]()
			{
				player->dotween->DoMoveY(player->mTransform.pos.y - 0.3f, 0.5f);
				player->dotween->Append(Vector3::zero, 0.3f, DoTween::FUNC::DELAY);
				player->dotween->Append(Vec3JumpPos, RISING_TIME, DoTween::FUNC::MOVE_Y);
				//WalkAfter();
				//MoveAfter();

			});

		// ���ɃW�����v����
		break;
	}
	default:

		WalkStart();

		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

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
			static_cast<int>(CGridObject::BlockType::CASTELLA))
		{
			// �ړ���̃J�X�e���̍��W
			CGrid::GRID_XY nextCastella = forwordPos;
			nextCastella.x += d.x;
			nextCastella.y += d.y;

			// �J�X�e���ړ���ɂ���炪����Ȃ�
			switch (static_cast<CGridObject::BlockType>
				(player->GetGridTable()->CheckObjectType(nextCastella)))
			{
			case CGridObject::BlockType::WALL:
			case CGridObject::BlockType::CAKE:
			case CGridObject::BlockType::CHILI:
			case CGridObject::BlockType::COIN:
			case CGridObject::BlockType::PROTEIN:
			case CGridObject::BlockType::GALL:
			case CGridObject::BlockType::GUMI:
			case CGridObject::BlockType::BAUMHORIZONTAL:
			case CGridObject::BlockType::BAUMVERTICAL:

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
