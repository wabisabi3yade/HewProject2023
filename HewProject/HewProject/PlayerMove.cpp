#include "PlayerMove.h"

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
	else
	{
		isMoving = true;
	}



	dotween->DoMove(_pos, 3.0f);
	dotween->OnComplete([&]{isMoving = false; });


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
