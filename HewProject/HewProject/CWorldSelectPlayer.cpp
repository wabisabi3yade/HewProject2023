#include "CWorldSelectPlayer.h"
#include "InputManager.h"
#include"CPlayerAnim.h"
#include "xa2.h"

CWorldSelectPlayer::CWorldSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex) :CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);

	// アニメーションを作成
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(0);
	mAnim->isStop = false;
	isMoving = false;
	isNoPush = false;
	isChangeScene = false;
	nNumSelectScene = 0;
}

CWorldSelectPlayer::~CWorldSelectPlayer()
{
	CLASS_DELETE(mAnim);
}

void CWorldSelectPlayer::Update()
{
	InputManager* input = InputManager::GetInstance();

	if (isMoving == false)
	{
		isNoPush = false;

		if (input->GetInputTrigger(InputType::DECIDE))
		{
			isMoving = true;
			isNoPush = true;

			Vector2 playerXY;
			playerXY.x = mTransform.pos.x;
			playerXY.y = mTransform.pos.y + 2.0f;

			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(0));

			dotween->DoMoveY(playerXY.y, 1.0f);

			dotween->OnComplete([&]() {isChangeScene = true; });

		}
	}

	if (isNoPush == false)
	{
		if (input->GetMovement().x < 0)
		{
			if (nNumSelectScene > 0)
			{
				XA_Play(SOUND_LABEL_SE000);
				isMoving = true;
				isNoPush = true;
				Vector2 playerXY;
				playerXY.x = mTransform.pos.x;
				playerXY.y = mTransform.pos.y;

				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(1));

				dotween->DoMoveX(playerXY.x, 3.0f);

				dotween->OnComplete([&]()
					{
						isMoving = false;
						nNumSelectScene--;

						if (nNumSelectScene < 0)
						{
							nNumSelectScene = 0;
						}

						dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int> (DIRECTION::LEFT));

					});
			}
			
		}

		if (input->GetMovement().x > 0)
		{
			if (nNumSelectScene < 4)
			{
				XA_Play(SOUND_LABEL_SE000);
				isMoving = true;
				isNoPush = true;
				Vector2 playerXY;
				playerXY.x = mTransform.pos.x;
				playerXY.y = mTransform.pos.y;

				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(0));

				dotween->DoMoveX(playerXY.x, 3.0f);

				dotween->OnComplete([&]()
					{
						isMoving = false;
						nNumSelectScene++;

						if (nNumSelectScene > 4)
						{
							nNumSelectScene = 4;
						}

						dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(DIRECTION::DOWN));

					});
			}
			

		}
	}

	dotween->Update();
	CObject::Update();
}

void CWorldSelectPlayer::Draw()
{
	CObject::Draw();
}

