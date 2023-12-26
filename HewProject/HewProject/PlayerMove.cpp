#include "PlayerMove.h"

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

	direction = DIRECTION::UP;
}

void PlayerMove::Update()
{
	dotween->Update();
}

PlayerMove::~PlayerMove()
{

}

void PlayerMove::Move(Vector3 _pos)
{
	if (isMoving) return;

	bool isInput = false;

	Vector3 target = Vector3::zero;

	if (gInput->GetKeyTrigger(VK_UP))
	{
		isInput = true;


	}
	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		isInput = true;
	}
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		isInput = true;
	}
	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		isInput = true;
	}

	if (isInput)
	{
		isMoving = true;
	}
}

void PlayerMove::SettingMove()
{
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}


	switch (direction)
	{
	case DIRECTION::UP:
		canMoveDir[static_cast<int>(DIRECTION::DOWN)] = false;
		break;

	case DIRECTION::DOWN:
		canMoveDir[static_cast<int>(DIRECTION::UP)] = false;
		break;

	case DIRECTION::RIGHT:
		canMoveDir[static_cast<int>(DIRECTION::LEFT)] = false;
		break;

	case DIRECTION::LEFT:
		canMoveDir[static_cast<int>(DIRECTION::RIGHT)] = false;
		break;
	}
}
