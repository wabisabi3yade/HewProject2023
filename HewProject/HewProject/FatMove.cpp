#include "FatMove.h"
#include "Player.h"
#include "CCastella.h"
#include"xa2.h"
FatMove::FatMove(Player* _p)
	: PlayerMove(_p)
{
	// �ړ��s�\�ȏ��̎�ނ����߂�
	cantMoveBlock = { 0, 2, 6, 7, 16 };
	IsMissMove = false;
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
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		// �ړ����I������P�[�L��H�ׂ�
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				XA_Play(SOUND_LABEL::S_EAT);
				player->dotween->DelayedCall(0.7f, [&]()
					{
						XA_Play(SOUND_LABEL::S_EAT);
					});
				player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				pos.z += 0.0001f;
				pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
				scale.x *= HEART_SCALE;
				scale.y *= HEART_SCALE;
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::HEART, false);
				// �H�׏I�������ړ��ł���悤�ɂ���
				player->dotween->DelayedCall(EAT_TIME, [&, pos, scale]()
					{
						player->EatEnd();
						player->EatCake();
						MoveAfter();
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
						player->EatEnd();
						player->EatChilli();
						MoveAfter();
						if (player->GetCalorie() < 11)
						{
							Vector3 pos = player->mTransform.pos;
							Vector3 scale = player->mTransform.scale;
							pos.z -= 0.000001f;
							pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
							scale.x *= SMOKE_SCALE;
							scale.y *= SMOKE_SCALE;
							XA_Play(SOUND_LABEL::S_CHANGE);
							player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_Y, false);
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
				WalkAfter();
				XA_Play(SOUND_LABEL::S_PROTEIN_DRINK);
				player->dotween->DelayedCall(0.5f, [&]()
					{
						XA_Play(SOUND_LABEL::S_PROTEIN_DRINK);
					});
				player->ChangeTexture(Player::ANIM_TEX::DRINK);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						MoveAfter();
						player->EatEnd();
						if (player->GetCalorie() < 11)
						{
							Vector3 pos = player->mTransform.pos;
							Vector3 scale = player->mTransform.scale;
							pos.z -= 0.000001f;
							pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
							scale.x *= SMOKE_SCALE;
							scale.y *= SMOKE_SCALE;
							XA_Play(SOUND_LABEL::S_CHANGE);
							player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_Y, false);
							player->Stop();
						}
						player->GetPlayerAnim()->StopWalk(player->GetDirection());
						player->ChangeTexture(Player::ANIM_TEX::WAIT);
					});
			});
		break;

	case CGridObject::BlockType::CASTELLA:

		WalkStart();
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
		player->SetIsCastellaPush(true);

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
							player->GetPlayerAnim()->StopWalk(player->GetDirection());
							player->ChangeTexture(Player::ANIM_TEX::WAIT);
							if (player->GetCalorie() < 11)
							{
								Vector3 pos = player->mTransform.pos;
								Vector3 scale = player->mTransform.scale;
								pos.z -= 0.000001f;
								pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
								scale.x *= SMOKE_SCALE;
								scale.y *= SMOKE_SCALE;
								XA_Play(SOUND_LABEL::S_CHANGE);
								player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_Y, false);
								player->Stop();
							}
						});
				});
		}
		else
		{
			player->dotween->OnComplete([&]()
				{
					WalkAfter();
					MoveAfter();
					player->GetPlayerAnim()->StopWalk(player->GetDirection());
					player->ChangeTexture(Player::ANIM_TEX::WAIT);
					if (player->GetCalorie() < 11)
					{
						Vector3 pos = player->mTransform.pos;
						Vector3 scale = player->mTransform.scale;
						pos.z -= 0.000001f;
						pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
						scale.x *= SMOKE_SCALE;
						scale.y *= SMOKE_SCALE;
						XA_Play(SOUND_LABEL::S_CHANGE);
						player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_Y, false);
						player->Stop();
					}
				});
		}

		break;

	case CGridObject::BlockType::CHOCO:
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
				//��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����
				WalkAfter();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
				fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				pos.z -= 0.00001f;
				scale.x *= MARK_SCALE;
				scale.y *= MARK_SCALE;
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::MARK, false);

				XA_Play(SOUND_LABEL::S_BIKKURI);
				player->dotween->DelayedCall(FALL_TIME / 2, [&]()
					{
						player->Fall();
						XA_Play(SOUND_LABEL::S_FLY_BATABATA);
					});
				player->dotween->DoDelay(FALL_TIME);
				player->dotween->DelayedCall(FALL_TIME, [&]()
					{
						XA_Play(SOUND_LABEL::S_FALL);
					});
				player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
				player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
				Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
				player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
				if (player->GetNowFloor() != 1)
				{
					if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
					{
						//�o�E���h���鍂�����v�Z�@���
						float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
						player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
						player->dotween->DelayedCall(FALLMOVE_TIME + FALLMOVE_TIME + FALL_TIME + FALLMOVE_TIME, [&]()
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
		//�W�����v���Ă��痎����悤��

		Vector2 junpPos = {};

		Vector3 Vec3JumpPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		junpPos.x = Vec3JumpPos.x;
		junpPos.y = Vec3JumpPos.y;
		XA_Play(SOUND_LABEL::S_JUNP);
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				XA_Play(SOUND_LABEL::S_FALL);
				////��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����
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
						//�o�E���h���鍂�����v�Z�@���
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
		//MoveAfter();

		player->dotween->Append(junpPos.y - 0.3f, 0.5f, DoTween::FUNC::MOVE_Y);
		player->dotween->OnComplete([&, Vec3JumpPos]()
			{
				player->dotween->DoDelay(0.3f);
				player->dotween->Append(Vec3JumpPos.y, RISING_TIME, DoTween::FUNC::MOVE_Y);
				player->dotween->DelayedCall(0.3f, [&]()
					{
						XA_Play(SOUND_LABEL::S_JUMP_GUMI);
					});
				player->Rise();
				player->dotween->DelayedCall(0.5f, [&]()
					{
						XA_Play(SOUND_LABEL::S_JUMP_UP);
					});
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

		// ���ɃW�����v����

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
		//��C�ɓ���Ƃ������ɍō��n�_�������̂𐧌䂷��
		float CurvePosControlVal = 1.0f;
		// ��O�̃}�X�ɍs���Ƃ��͐��Z���W����O�ɍ��킹��
		if (_dir != DIRECTION::UP || _dir != DIRECTION::RIGHT)
		{
			player->mTransform.pos.z = forwardPos.z - 0.20001f;
			CurvePosControlVal = 0.7f;
		}
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME, junpPos.y + (CANNON_IN_CURVE_POS_Y * player->GetGridTable()->GetGridScale().y));
		player->dotween->Append(forwardPos.z - 0.20001f, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				player->SetGridPos(nextGridPos);
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				player->GetPlayerMove()->InCannon();
			});
		break;
	}
	default:

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
				MoveAfter();
				if (player->GetCalorie() < 11)
				{
					Vector3 pos = player->mTransform.pos;
					Vector3 scale = player->mTransform.scale;
					pos.z -= 0.000001f;
					pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
					scale.x *= SMOKE_SCALE;
					scale.y *= SMOKE_SCALE;
					XA_Play(SOUND_LABEL::S_CHANGE);
					player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_Y, false);
					player->Stop();
				}
			});
		break;
	}
}

void FatMove::Step()
{
	switch (player->GetPlayerMove()->CheckNextMassType())
	{
	case CGridObject::BlockType::CAKE:
	{
		WalkStart();
		// �H�׏I�������ړ��ł���悤�ɂ���
		XA_Play(SOUND_LABEL::S_EAT);
		player->dotween->DelayedCall(0.7f, [&]()
			{
				XA_Play(SOUND_LABEL::S_EAT);
			});
		player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
		player->GetPlayerAnim()->PlayEat(player->GetDirection());

		Vector3 pos = player->mTransform.pos;
		Vector3 scale = player->mTransform.scale;
		pos.z -= 0.000001f;
		scale.x *= HEART_SCALE;
		scale.y *= HEART_SCALE;
		player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::HEART, false);

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
				FallAfter();
				player->EatCake();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
			});
		break;
	}
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
	case CGridObject::BlockType::CHOCOCRACK:
	{
		//��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����
		Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
		fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
		player->dotween->DelayedCall(FALL_TIME / 2, [&]()
			{
				player->Fall();
			});
		player->dotween->DoDelay(FALL_TIME);
		player->dotween->DelayedCall(FALL_TIME, [&]()
			{
				XA_Play(SOUND_LABEL::S_FALL);
			});
		player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
		player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
		Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
		if (player->GetNowFloor() != 1)
		{
			if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
			{
				//�o�E���h���鍂�����v�Z�@���
				float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
				player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
				player->dotween->DelayedCall(FALL_TIME + FALLMOVE_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
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
		break;
	}
	case CGridObject::BlockType::HOLL:
	{
		//WalkStart();
		//�W�����v���Ă��痎����悤��

		Vector3 fallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::FLOOR));
		fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f) - 0.1f;
		Vector2 fallPosXY;
		fallPosXY.x = fallPos.x;
		fallPosXY.y = fallPos.y;
		player->Fall();

		XA_Play(SOUND_LABEL::S_FALL);
		player->dotween->DoMoveXY(fallPosXY, FALLMOVE_TIME);
		//player->dotween->Append(fallPos, FALLMOVE_TIME, DoTween::FUNC::MOVE_XY);
		player->dotween->Append(Vector3::zero, FALLMOVE_TIME, DoTween::FUNC::DELAY);
		Vector3 floorFallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START));
		player->dotween->Append(floorFallPos.y, FALLMOVE_TIME, DoTween::FUNC::MOVE_Y);
		if (player->GetNowFloor() != 1)
		{
			if (player->GetNextGridTable()->CheckFloorType(player->GetPlayerMove()->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
			{
				//�o�E���h���鍂�����v�Z�@���
				float BoundPosY = floorFallPos.y + 0.3f + BOUND_CURVE_POS_Y * nextGridPos.y;
				player->dotween->Append(floorFallPos, BOUND_TIME, DoTween::FUNC::MOVECURVE, BoundPosY);
				player->dotween->DelayedCall(FALLMOVE_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
					{
						XA_Play(SOUND_LABEL::S_TYAKUTI);
						isFallBound = true;
					});
			}
		}
		player->dotween->DelayedCall(FALLMOVE_TIME , [&]()
			{
				player->fallMoveTrriger = true;
			});


	}
	break;

	case CGridObject::BlockType::GUMI:
	{
		MoveAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		// ���ɃW�����v����
	}
	break;

	case CGridObject::BlockType::CANNON:
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->GetPlayerMove()->InCannon();
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		player->SetGridPos(nextGridPos);
		break;

	default:	// ��
		MoveAfter();
		FallAfter();
		if (player->GetCalorie() < 11)
		{
			Vector3 pos = player->mTransform.pos;
			Vector3 scale = player->mTransform.scale;
			pos.z -= 0.000001f;
			pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
			scale.x *= SMOKE_SCALE;
			scale.y *= SMOKE_SCALE;
			XA_Play(SOUND_LABEL::S_CHANGE);
			player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_Y, false);
			player->Stop();
		}
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);

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
			|| player->GetGridTable()->floorTable[forwordPos.y][forwordPos.x] == 0
			|| forwordPos.x > 8 || forwordPos.y > 8)
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
