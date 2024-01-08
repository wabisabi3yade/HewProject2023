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

	// ���������̓}�X�ɉ������s��������
	// �ړ���̍��W
	Vector3 forwardPos = player->GetGridTable()->GridToWorld(nextGridPos, CStageMake::BlockType::START);

	// �i�񂾐�̃u���b�N�ɂ���đΉ�����A�N�V������ݒ肷��
	switch (CheckNextMassType())
	{
	case CStageMake::BlockType::CAKE:
		// �ړ�����
		player->dotween->DoMove(forwardPos, WALK_TIME);
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
		player->dotween->DoMove(forwardPos, WALK_TIME);
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
		player->dotween->DoMove(forwardPos, WALK_TIME);
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
		player->dotween->DoMove(forwardPos, WALK_TIME);
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
