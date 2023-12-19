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
	//static float time = 0.0f;
	//static bool o_isMove = false;;

	//// 移動後isMovingをfalseにする処理（仮）
	//if (!o_isMove && isMoving)
	//{
	//	time = 0.0f;
	//}

	Move();

	//if (isMoving)
	//{
	//	time += 1.0f / 60.0f;

	//	if (time >= moveTime)
	//	{
	//		isMoving = false;
	//		time = 0.0f;
	//	}
	//}



	//o_isMove = isMoving;
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

		target = { 6.0f, 3.0f, 1.0f };
		dotween->DoMove(target, 1.0f);
		target = { 2.0f, 2.0f, 1.0f };
		dotween->Append(target, 0.5f, DoTween::FUNC::SCALE);
		target = { 1.0f, 1.0f, 1.0f };
		dotween->Append(target, 0.5f, DoTween::FUNC::SCALE);

		target = { 6.0f, -3.0f, 1.0f };
		dotween->Append(target, 1.0f, DoTween::FUNC::MOVE);
		target = { 2.0f, 2.0f, 1.0f };
		dotween->Append(target, 0.5f, DoTween::FUNC::SCALE);
		target = { 1.0f, 1.0f, 1.0f };
		dotween->Append(target, 0.5f, DoTween::FUNC::SCALE);

		target = { -6.0f, -3.0f, 1.0f };
		dotween->Append(target, 1.0f, DoTween::FUNC::MOVE);
		target = { 2.0f, 2.0f, 1.0f };
		dotween->Append(target, 0.5f, DoTween::FUNC::SCALE);
		target = { 1.0f, 1.0f, 1.0f };
		dotween->Append(target, 0.5f, DoTween::FUNC::SCALE);

		target = { -6.0f, 3.0f, 1.0f };
		dotween->Append(target, 1.0f, DoTween::FUNC::MOVE);
		target = { 2.0f, 2.0f, 1.0f };
		dotween->Append(target, 0.5f, DoTween::FUNC::SCALE);
		target = { 1.0f, 1.0f, 1.0f };
		dotween->Append(target, 0.5f, DoTween::FUNC::SCALE);

		dotween->SetLoop(3);

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
