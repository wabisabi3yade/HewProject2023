#include "PlayerMove.h"

#include "Vector3.h"
#include "CInput.h"
#include "DoTween.h"
#include "Player.h"
#include<functional>

typedef std::function<void(void)> Func;

PlayerMove::PlayerMove(Player* _p)
{
	// ポインタを取得する
	player.reset(_p);

	dotween = std::make_unique<DoTween>(player.get());

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
	/*if (isoving) return;*/

	Vector3 target = Vector3::zero;

	if (gInput->GetKeyTrigger(VK_UP))
	{
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
