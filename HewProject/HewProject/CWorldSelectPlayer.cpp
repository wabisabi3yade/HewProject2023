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

			dotween->OnComplete([&]() { isMoving = false; });
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

			dotween->OnComplete([&]() { isMoving = false; });

		}
	}



	dotween->Update();
	CObject::Update();
}

void CWorldSelectPlayer::Draw()
{
	CObject::Draw();
}
