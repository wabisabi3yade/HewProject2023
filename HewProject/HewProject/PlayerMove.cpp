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
	isMoving = false;
	isMovingLast = false;
	isMovingTrigger = false;

	direction = DIRECTION::UP;
}

void PlayerMove::Update()
{
	dotween->Update();
	if (!isMoving && isMovingLast)
	{
		isMovingTrigger = true;
		SettingMove();
	}
	else
	{
		isMovingTrigger = false;
	}
	isMovingLast = isMoving;
}

PlayerMove::~PlayerMove()
{

}

void PlayerMove::Move(Vector3 _nowpos, Vector3 _targetpos)
{
	if (isMoving) return;

	if (_targetpos.x > _nowpos.x && _targetpos.y > _nowpos.y)
	{
		if (canMoveDir[(int)DIRECTION::RIGHT] != false)
		{
			direction = DIRECTION::RIGHT;
			isMoving = true;
			dotween->DoMove(_targetpos, 3.0f);
			dotween->OnComplete([&] {isMoving = false; });

		}
	}
	else if (_targetpos.x < _nowpos.x && _targetpos.y < _nowpos.y)
	{
		if (canMoveDir[(int)DIRECTION::LEFT] != false)
		{
			direction = DIRECTION::LEFT;
			isMoving = true;
			dotween->DoMove(_targetpos, 3.0f);
			dotween->OnComplete([&] {isMoving = false; });

		}
	}
	else if (_targetpos.y < _nowpos.y && _targetpos.x > _nowpos.x)
	{
		if (canMoveDir[(int)DIRECTION::DOWN] != false)
		{
			direction = DIRECTION::DOWN;
			isMoving = true;
			dotween->DoMove(_targetpos, 3.0f);
			dotween->OnComplete([&] {isMoving = false; });

		}
	}
	else if (_targetpos.y > _nowpos.y && _targetpos.x < _nowpos.x)
	{
		if (canMoveDir[(int)DIRECTION::UP] != false)
		{
			isMoving = true;
			direction = DIRECTION::UP;
			dotween->DoMove(_targetpos, 3.0f);
			dotween->OnComplete([&] {isMoving = false; });

		}
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
