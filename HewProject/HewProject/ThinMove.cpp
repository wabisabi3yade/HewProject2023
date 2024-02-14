#include "ThinMove.h"
#include "Player.h"
#include "CBaum.h"

ThinMove::ThinMove(Player* _p)
	: PlayerMove(_p)
{
	// �ړ��s�\�ȏ��̎�ނ����߂�
	cantMoveBlock = { 0, 2, 5, 16 };
}

void ThinMove::Move(DIRECTION _dir)
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
				//���p��
				pos = player->mTransform.pos;
				pos.z -= 0.000001f;
				pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
				scale = player->mTransform.scale;
				scale.x *= SMOKE_SCALE;
				scale.y *= SMOKE_SCALE;
				// �H�׏I�������ړ��ł���悤�ɂ���
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						player->EatEnd();
						player->EatCake();
						MoveAfter();
						player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_Y, false);
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
		// ���ɂ�����Ƃ��̃W�����v

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
					case 3:
					{
						player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
						Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
						player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
						if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
						{
							//�o�E���h���鍂�����v�Z�@���
							//player->Fall();
							float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
							player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
							//player->dotween->DoMoveCurve({ floorFallPos.x,floorFallPos.y }, BOUND_TIME, BoundPosY);
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
		//MoveAfter();
		//WalkAfter();
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

		// ���ɃW�����v����

	}
	break;

	case CGridObject::BlockType::BAUMHORIZONTAL:
	case CGridObject::BlockType::BAUMVERTICAL:
	{
		CGrid::GRID_XY nextGridPosCopy = nextGridPos;
		// �o�E���N�[�w���̌��������Ɉړ�����
		// �������ɍ��W�ݒ�
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
		
		// �v���C���[���ړ������Ă���
		player->mTransform.pos = forwardPos;


		Vector2 baumAdjustPos = Vector2::zero;
		// �o�E���N�[�w�����������W
		switch (_dir)
		{
		case DIRECTION::DOWN:
			baumAdjustPos = { 0,0 };
			break;

		case DIRECTION::UP:
			baumAdjustPos = { 0,0 };
			break;

		case DIRECTION::RIGHT:
			baumAdjustPos = { 0,0 };
			break;


		case DIRECTION::LEFT:
			baumAdjustPos = { -0.013f, 0.103f };
			break;
		}
		player->mTransform.pos.x += baumAdjustPos.x * player->GetGridTable()->GetGridScale().x;
		player->mTransform.pos.y += baumAdjustPos.y * player->GetGridTable()->GetGridScale().y;

		// �����I�������
		player->dotween->DelayedCall(BAUM_THROWENDTIME , [&, nextGridPosCopy]()
			{
				WalkAfter();
				// �J�X�e����������Ƀu���b�N�ɂ���ď���������
				switch (static_cast<CGridObject::BlockType>(player->GetGridTable()->CheckMassType(nextGridPosCopy)))
				{
				case CGridObject::BlockType::CAKE:
					// �H�׏I�������ړ��ł���悤�ɂ���
					player->dotween->DelayedCall(EAT_TIME, [&]()
						{
							nextGridPos = nextGridPosCopy;
							player->EatCake();
							MoveAfter();
							player->GetPlayerAnim()->StopWalk(player->GetDirection());
							player->ChangeTexture(Player::ANIM_TEX::WAIT);
						});
					break;

				case CGridObject::BlockType::CHILI:
					// �H�׏I�������ړ��ł���悤�ɂ���
					player->dotween->DelayedCall(EAT_TIME, [&]()
						{
							nextGridPos = nextGridPosCopy;
							player->EatChilli();
							MoveAfter();
							player->GetPlayerAnim()->StopWalk(player->GetDirection());
							player->ChangeTexture(Player::ANIM_TEX::WAIT);
						});
					break;

				case CGridObject::BlockType::PROTEIN:
					player->dotween->DelayedCall(EAT_TIME, [&]()
						{
							nextGridPos = nextGridPosCopy;
							MoveAfter();
							player->GetPlayerAnim()->StopWalk(player->GetDirection());
							player->ChangeTexture(Player::ANIM_TEX::WAIT);
						});
					break;

				case CGridObject::BlockType::COIN:
					nextGridPos = nextGridPosCopy;
					MoveAfter();
					player->GetPlayerAnim()->StopWalk(player->GetDirection());
					player->ChangeTexture(Player::ANIM_TEX::WAIT);
					break;

				case CGridObject::BlockType::CHOCO:
					nextGridPos = nextGridPosCopy;
					MoveAfter();
					player->GetPlayerAnim()->StopWalk(player->GetDirection());
					player->ChangeTexture(Player::ANIM_TEX::WAIT);
					break;

				case CGridObject::BlockType::CHOCOCRACK:
					nextGridPos = nextGridPosCopy;
					MoveAfter();
					player->GetPlayerAnim()->StopWalk(player->GetDirection());
					player->ChangeTexture(Player::ANIM_TEX::WAIT);

					//player->dotween->OnComplete([&]()
					//	{
					//		WalkAfter();
					//		//��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����
					//		Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
					//		fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
					//		player->dotween->DelayedCall(FALL_TIME / 2, [&]()
					//			{
					//				player->Fall();
					//			});
					//		player->dotween->DoDelay(FALL_TIME);
					//		player->dotween->Append(fallPos, WALK_TIME, DoTween::FUNC::MOVE_XY);
					//	});
					break;

				case CGridObject::BlockType::HOLL:
				{
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
					case 3:
					{
						player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
						Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
						player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
						if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
						{
							//�o�E���h���鍂�����v�Z�@���
							//player->Fall();
							float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
							player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
							//player->dotween->DoMoveCurve({ floorFallPos.x,floorFallPos.y }, BOUND_TIME, BoundPosY);
						}
						player->dotween->DelayedCall(FALLMOVE_TIME, [&]()
							{
								player->fallMoveTrriger = true;
							});


					}
					}
				}
				default:
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
		if (_dir != DIRECTION::UP || _dir != DIRECTION::RIGHT)
		{
			player->mTransform.pos.z = forwardPos.z - 0.20001f;
		}
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME,junpPos.y + (CANNON_IN_CURVE_POS_Y * player->GetGridTable()->GetGridScale().y));
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
		// �H�׏I�������ړ��ł���悤�ɂ���
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
	case CGridObject::BlockType::CHOCO:

		MoveAfter();
		FallAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		break;
	case CGridObject::BlockType::CHOCOCRACK:
	{

		WalkStart();
		WalkAfter();
		//��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����			
		Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
		fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
		player->dotween->DelayedCall(FALL_TIME / 2, [&]()
			{
				player->Fall();
			});
		player->dotween->DoDelay(FALL_TIME);
		player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
		break;

	}
	case CGridObject::BlockType::HOLL:
	{


		WalkStart();
		//�W�����v���Ă��痎����悤��

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
		case 3:
		{
			player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
			Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
			player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
			if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
			{
				//�o�E���h���鍂�����v�Z�@���
				//player->Fall();
				float BoundPosY = floorFallPos.y + player->mTransform.scale.y / 2;
				player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
				//player->dotween->DoMoveCurve({ floorFallPos.x,floorFallPos.y }, BOUND_TIME, BoundPosY);
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
		// ���ɃW�����v����
	}
	break;

	case CGridObject::BlockType::CANNON:

		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		player->GetPlayerMove()->InCannon();

		break;

	default:	// ��
		MoveAfter();
		FallAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		break;
	}
}

void ThinMove::CheckCanMove()
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

		// �o�E���N�[�w���̕����ōs���邩�m�F����
		// �ړ��悪�������o�E���@���@�ړ��������c�Ȃ�
		if (player->GetGridTable()->CheckObjectType(forwordPos) ==
			static_cast<int>(CGridObject::BlockType::BAUMHORIZONTAL) &&
			d.y != 0)
		{
			canMoveDir[dirRoop] = false;
			continue;
		}
		// �ړ��悪�c�����o�E���@���@�ړ����������Ȃ�
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
