#include "PlayerMove.h"

#include "Vector3.h"
#include "CInput.h"
#include "DoTween.h"
#include "Player.h"

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
	static float time = 0.0f;
	static bool o_isMove = false;;

	if (!o_isMove && isMoving)
	{
		time = 0.0f;
	}

	Move();

	if (isMoving)
	{
		time += 1.0f / 60.0f;

		if (time >= moveTime)
		{
			isMoving = false;
			time = 0.0f;
		}
	}
	


	o_isMove = isMoving;
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
		/*isMoving = true;
		target = {player->mTransform.pos.x};
		dotween->DoMove();*/
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
