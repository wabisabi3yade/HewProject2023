#include "PlayerMove.h"

#include "Vector3.h"
#include "CInput.h"
#include "DoTween.h"
#include "Player.h"

PlayerMove::PlayerMove(Player* _p)
{
	// ポインタを取得する
	player.reset(_p);

	dotween = std::make_unique<DoTween>();

	// 移動可能フラグをONにする
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
	if (isMoving) return;

	Vector3 target = Vector3::zero;

	if (gInput->GetKeyTrigger(VK_UP))
	{
		isMoving = true;
		target.y = player->mTransform.pos.y + 2.0f;
		dotween->DoMove((CObject*)player.get(), target, 2.0f);
	}
	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		isMoving = true;
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
