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

	bool isInput = false;

	Vector3 target = Vector3::zero;

	if (gInput->GetKeyTrigger(VK_UP))
	{
		isInput = true;

		target = Vector3::zero;
		target.z = player->mTransform.rotation.z + 90.0f;
		dotween->DoRotation(target, 1.0f);

		dotween->OnComplete
		([&]() {
			isMoving = false;
			});

	}
	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		isInput = true;

		target = { 6.0f, 3.0f, 1.0f };
		dotween->DoMove(target, 1.0f);

		target = Vector3::zero;
		target.z = player->mTransform.rotation.z += 90.0f;
		dotween->Join(target, 2.0f, DoTween::FUNC::ROTATION);

		dotween->OnComplete
		([&]() {
			isMoving = false;
			});
	}
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		isInput = true;

		dotween->OnComplete
		([&]() {
			isMoving = false;
			});
	}
	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		isInput = true;

		dotween->OnComplete
		([&]() {
			isMoving = false;
			});
	}

	if (isInput)
	{
		isMoving = true;
	}
}
