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
		Vector3 target = Vector3::zero;

		target = { 2.0f, 2.0f,1.0f };
		// シーケンスの最初の処理はDo～の関数から始める
		dotween->DoMove(target, 2.0f);	// 移動

		target = { 0.0f,0.0f,player->mTransform.rotation.z + 90.0f };
		// 前の処理と同じタイミングで始める
		dotween->Join(target, 2.0f, DoTween::FUNC::ROTATION);	// 回転

		target = { player->mTransform.scale.x + 2.0f,
				   player->mTransform.scale.y + 2.0f,
				   1.0f };
		// 前の処理が終わると始める
		dotween->Append(target, 2.0f, DoTween::FUNC::SCALE);	// 拡大

		dotween->Join(-3.0f, 2.0f, DoTween::FUNC::MOVE_Y);

		dotween->SetLoop(3);	// 上の処理を3回繰り返す

		// 上の処理が終わるとスケールを戻す
		dotween->OnComplete
		([&]() {
			player->mTransform.scale.x = 1.0f;
			player->mTransform.scale.y = 1.0f;
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
