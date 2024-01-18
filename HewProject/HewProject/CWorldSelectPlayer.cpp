#include "CWorldSelectPlayer.h"
#include "CInput.h"
#include"CPlayerAnim.h"

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
	nNumSelectScene = 2;
}

CWorldSelectPlayer::~CWorldSelectPlayer()
{
	CLASS_DELETE(mAnim);
}

void CWorldSelectPlayer::Update()
{
	if (isMoving == false)
	{
		dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk();
		isNoPush = false;

		if (gInput->GetKeyTrigger(VK_RETURN))
		{
			isMoving = true;

			Vector2 playerXY;
			playerXY.x = mTransform.pos.x;
			playerXY.y = mTransform.pos.y + 2.0f;

			dotween->DoMoveY(playerXY.y, 1.0f);

			dotween->OnComplete([&]() {isChangeScene = true; });

		}
	}

	if (isNoPush == false)
	{
		if (gInput->GetKeyTrigger(VK_LEFT))
		{
			isMoving = true;
			isNoPush = true;
			Vector2 playerXY;
			playerXY.x = mTransform.pos.x - 3.0f;
			playerXY.y = mTransform.pos.y;

			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(1));

			dotween->DoMoveX(playerXY.x, 2.0f);

			dotween->OnComplete([&]()
				{
					isMoving = false;
					nNumSelectScene--;

					if (nNumSelectScene < 0)
					{
						nNumSelectScene = 0;
					}

				});
		}

		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			isMoving = true;
			isNoPush = true;
			Vector2 playerXY;
			playerXY.x = mTransform.pos.x + 3.0f;
			playerXY.y = mTransform.pos.y;

			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(0));

			dotween->DoMoveX(playerXY.x, 2.0f);

			dotween->OnComplete([&]()
				{
					isMoving = false;
					nNumSelectScene++;

					if (nNumSelectScene > 4)
					{
						nNumSelectScene = 4;
					}

				});

		}
	}

	dotween->Update();
	CObject::Update();
}

void CWorldSelectPlayer::Draw()
{
	CObject::Draw();
}

void CWorldSelectPlayer::FlagInit()
{
	mAnim->SetPattern(0);
	mAnim->isStop = false;
	isMoving = false;
	isNoPush = false;
	isChangeScene = false;
	nNumSelectScene = 2;
}
