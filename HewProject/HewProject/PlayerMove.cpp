#include "PlayerMove.h"

#include "Vector3.h"
#include "CInput.h"
#include "DoTween.h"
#include "Player.h"

PlayerMove::PlayerMove(Player* _p)
{
	// �|�C���^���擾����
	player.reset(_p);

	dotween = std::make_unique<DoTween>(player.get());

	// �ړ��\�t���O��ON�ɂ���
	isMoving = false;;
}

void PlayerMove::Update()
{
	Move();

	dotween->Update();
}

PlayerMove::~PlayerMove()
{
	
}

void PlayerMove::Move()
{
	/*if (isMoving) return;*/

	Vector3 target = Vector3::zero;

	if (gInput->GetKeyTrigger(VK_UP))
	{
		isMoving = true;

		target = { 2.0f, 2.0f,2.0f };
		dotween->DoScale(target, 2.0f);
		
		target = { 0.5f, 0.5f, 0.5f };
		dotween->Append(target, 2.0f,DoTween::FUNC::SCALE);

		dotween->SetLoop(3);

	}
	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		isMoving = true;

		target.x = player->mTransform.pos.x + 2.0f;
		dotween->DoMove(target, 2.0f);

		target = { 0.0f, 0.0f, 90.0f };

		dotween->Append(-2.0f, 2.0f, DoTween::FUNC::MOVE_Y);
	}
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		isMoving = true;
	}
	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		isMoving = true;
	}
}
