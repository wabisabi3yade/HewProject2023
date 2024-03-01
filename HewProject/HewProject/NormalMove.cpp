#include "NormalMove.h"
#include "Player.h"
#include"xa2.h"
NormalMove::NormalMove(Player* _p)
	: PlayerMove(_p)
{
	// �ړ��s�\�ȏ��̎�ނ����߂�
	cantMoveBlock = { 0, 2, 5, 6, 7, 16 };
}

void NormalMove::Move(DIRECTION _dir)
{
	// �ړ��t���O��true
	isMoving = true;
	isMoveStartTrigger = true;

	// ������ݒ肷��
	player->SetDirection(static_cast<int>(_dir));

	//	�ړ���̃O���b�h���W
	nextGridPos = player->GetGridPos();

	switch (_dir)
	{
	case DIRECTION::UP:
		nextGridPos.y += -1;
		break;

	case DIRECTION::DOWN:
		nextGridPos.y += 1;
		break;

	case DIRECTION::RIGHT:
		nextGridPos.x += 1;
		break;

	case DIRECTION::LEFT:
		nextGridPos.x += -1;
		break;
	}

	// �ړ���̍��W
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::START, static_cast<int>(player->GetState()));
	Vector2 forwardPosXY = { forwardPos.x, forwardPos.y };

	// �����ɍs�����ǂ���
	bool backMove = false;

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

	// ���������̓}�X�ɉ������s��������
	// �i�񂾐�̃u���b�N�ɂ���đΉ�����A�N�V������ݒ肷��
	switch (CheckNextMassType())
	{
	case CGridObject::BlockType::CAKE:

		WalkStart();
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
		// �ړ�����
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		// �ړ����I������P�[�L��H�ׂ�
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				Vector3 pos = player->mTransform.pos;
				Vector3 scale = player->mTransform.scale;
				XA_Play(SOUND_LABEL::S_EAT);
				player->dotween->DelayedCall(0.7f, [&]()
					{
						XA_Play(SOUND_LABEL::S_EAT);
					});
				player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				pos.z += 0.001000f;
				scale.x *= HEART_SCALE;
				scale.y *= HEART_SCALE;
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::HEART, false);

				pos = player->mTransform.pos;
				scale = player->mTransform.scale;
				pos.z -= 0.000001f;
				pos.y += 0.5f * player->GetGridTable()->GetGridScale().y;
				scale.x *= SMOKE_SCALE;
				scale.y *= SMOKE_SCALE;
				// �H�׏I�������ړ��ł���悤�ɂ���
				player->dotween->DelayedCall(EAT_TIME, [&, pos, scale]()
					{
						MoveAfter();
						XA_Play(SOUND_LABEL::S_CHANGE);
						player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_G, false);
						player->EatEnd();
						player->Stop();
						player->EatCake();
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
				XA_Play(SOUND_LABEL::S_PROTEIN_DRINK);
				player->dotween->DelayedCall(0.5f, [&]()
					{
						XA_Play(SOUND_LABEL::S_PROTEIN_DRINK);
					});
				player->ChangeTexture(Player::ANIM_TEX::DRINK);
				player->GetPlayerAnim()->PlayEat(player->GetDirection());
				WalkAfter();
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
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
						player->EatEnd();
						player->GetPlayerAnim()->StopWalk(player->GetDirection());
						player->ChangeTexture(Player::ANIM_TEX::WAIT);
					});
			});
		break;

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
				pos.z -= 0.000001f;
				scale.x *= MARK_SCALE;
				scale.y *= MARK_SCALE;
				player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::MARK, false);
				XA_Play(SOUND_LABEL::S_BIKKURI);
				player->dotween->DelayedCall(FALL_TIME / 2, [&]()
					{
						player->Fall();
						XA_Play(SOUND_LABEL::S_FLY_BATABATA);
					});
				player->dotween->DelayedCall(FALL_TIME, [&]()
					{
						XA_Play(SOUND_LABEL::S_FALL);
					});
				player->dotween->DoDelay(FALL_TIME);
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
						player->dotween->DelayedCall(FALLMOVE_TIME + FALL_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
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
				////��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����

				XA_Play(SOUND_LABEL::S_FALL);
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
		player->dotween->Append(junpPos.y - 0.3f, 0.5f, DoTween::FUNC::MOVE_Y);
		player->dotween->OnComplete([&, Vec3JumpPos]()
			{
				player->dotween->DelayedCall(0.3f, [&]()
					{
						XA_Play(SOUND_LABEL::S_JUMP_GUMI);
					});
				player->dotween->DoDelay(0.3f);
				player->dotween->Append(Vec3JumpPos.y, RISING_TIME, DoTween::FUNC::MOVE_Y);
				player->Rise();
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
		player->dotween->DoMoveCurve(junpPos, JUMP_TIME, junpPos.y + (CANNON_IN_CURVE_POS_Y * CurvePosControlVal * player->GetGridTable()->GetGridScale().y));
		player->dotween->Append(forwardPos.z - 0.20001f, 0.0f, DoTween::FUNC::MOVE_Z);

		player->dotween->OnComplete([&]()
			{
				player->SetGridPos(nextGridPos);
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				player->GetPlayerMove()->InCannon();
			});
	}
	break;
	default:	// ��

		WalkStart();
		XA_Play(SOUND_LABEL::S_WALK);
		player->dotween->DelayedCall(0.5f, [&]()
			{
				XA_Play(SOUND_LABEL::S_WALK);
			});
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);
		player->dotween->OnComplete([&]() {
			WalkAfter();
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
			});
		break;
	}
}


void NormalMove::Step()
{
	switch (player->GetPlayerMove()->CheckNextMassType())
	{
	case CGridObject::BlockType::CAKE:

		XA_Play(SOUND_LABEL::S_EAT);
		player->dotween->DelayedCall(0.7f, [&]()
			{
				XA_Play(SOUND_LABEL::S_EAT);
			});
		player->ChangeTexture(Player::ANIM_TEX::EAT_CAKE);
		player->GetPlayerAnim()->PlayEat(player->GetDirection());
		// �H�׏I�������ړ��ł���悤�ɂ���
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
				player->Stop();
				player->EatCake();
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				FallAfter();
			});

		break;

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
				player->GetPlayerAnim()->StopWalk(player->GetDirection());
				player->ChangeTexture(Player::ANIM_TEX::WAIT);
				FallAfter();
				player->EatChilli();
				player->EatEnd();
				FallAfter();
			});
		break;

	case CGridObject::BlockType::PROTEIN:

		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
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
	case CGridObject::BlockType::CHOCO:
		//WalkStart();
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
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		FallAfter();
		break;
	case CGridObject::BlockType::CHOCOCRACK:
	{

		if (!isFalling)
		{

			WalkStart();

			//��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����


			XA_Play(SOUND_LABEL::S_FALL);
			player->GetPlayerAnim()->StopWalk(player->GetDirection());
			Vector3 fallPos(player->GetGridTable()->GridToWorld(nextGridPos, CGridObject::BlockType::FLOOR));
			fallPos.y = (FALL_POS_Y)-(player->mTransform.scale.y / 2.0f);
			Vector3 pos = player->mTransform.pos;
			Vector3 scale = player->mTransform.scale;
			pos.z -= 0.000001f;
			scale.x *= MARK_SCALE;
			scale.y *= MARK_SCALE;
			player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::MARK, false);
			player->dotween->DelayedCall(0.5f, [&]()
				{
					XA_Play(SOUND_LABEL::S_BIKKURI);
				});
			player->dotween->DelayedCall(FALL_TIME / 2, [&]()
				{
					player->Fall();
					XA_Play(SOUND_LABEL::S_FLY_BATABATA);
				});
			player->dotween->DoDelay(FALL_TIME);
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
					player->dotween->DelayedCall(FALLMOVE_TIME + FALL_TIME + FALLMOVE_TIME + FALLMOVE_TIME, [&]()
						{
							XA_Play(SOUND_LABEL::S_TYAKUTI);
							isFallBound = true;
						});
				}
			}
			player->dotween->DelayedCall(FALLMOVE_TIME + FALLMOVE_TIME, [&]()
				{
					player->fallMoveTrriger = true;
				});
		}
		else
		{
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
			}
			player->GetPlayerAnim()->StopWalk(player->GetDirection());
			player->ChangeTexture(Player::ANIM_TEX::WAIT);
			player->dotween->DelayedCall(0.1f, [&]()
				{
					FallAfter();
				});
		}
		break;
	}
	case CGridObject::BlockType::HOLL:
	{
		//WalkStart();
		//�W�����v���Ă��痎����悤��

		XA_Play(SOUND_LABEL::S_FALL);
		//��ʊO�܂ňړ�����悤��Y���}�N���Œ�`���Ďg�p����
		Vector3 fallPos(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::FLOOR));
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


	}
	break;

	case CGridObject::BlockType::GUMI:
	{

		//WalkStart();
		MoveAfter();
		FallAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);

		//MoveAfter();
		// ���ɃW�����v����

	}
	break;

	case CGridObject::BlockType::CANNON:

		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		player->GetPlayerMove()->InCannon();
		player->SetGridPos(nextGridPos);

		break;

	default:	// ��
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
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		player->ChangeTexture(Player::ANIM_TEX::WAIT);
		FallAfter();
		player->GetPlayerAnim()->StopWalk(player->GetDirection());
		//player->ChangeTexture(Player::ANIM_TEX::WAIT);
		break;
	}
}

void NormalMove::CheckCanMove()
{
	PlayerMove::CheckCanMove();
}

NormalMove::~NormalMove()
{
}
