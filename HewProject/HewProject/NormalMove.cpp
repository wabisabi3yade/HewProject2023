#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include "NormalMove.h"
#include "Player.h"

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
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CStageMake::BlockType::START);
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
	case CStageMake::BlockType::CAKE:
		// �ړ�����
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);

		// �ړ����I������P�[�L��H�ׂ�
		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				// �H�׏I�������ړ��ł���悤�ɂ���
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						player->EatCake();
						MoveAfter();
					});
			});
		break;

	case CStageMake::BlockType::CHILI:
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);


		player->dotween->OnComplete([&]()
			{
				WalkAfter();
				player->dotween->DelayedCall(EAT_TIME, [&]()
					{
						player->EatChilli();
						MoveAfter();
					});
			});
		break;

	case CStageMake::BlockType::HOLL:
		// ���ɂ�����Ƃ��̃W�����v
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);


		player->dotween->OnComplete([&]()
			{
				// ���ɗ��������̏���������
				// ���������Ă��Ȃ����󏰂Ɠ��������ɂ��Ă�
				WalkAfter();
				MoveAfter();
			});
		break;

	case CStageMake::BlockType::GUMI:
		// ���ɃW�����v����

		break;

	default:	// ��
		player->dotween->DoMoveXY(forwardPosXY, WALK_TIME);
		player->dotween->Append(forwardPos.z, 0.0f, DoTween::FUNC::MOVE_Z);


		player->dotween->OnComplete([&]() {WalkAfter(); MoveAfter(); });
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
