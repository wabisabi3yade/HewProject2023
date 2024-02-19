#include "CGameClearPlayer.h"
#include"CPlayerAnim.h"

CGameClearPlayer::CGameClearPlayer(D3DBUFFER vb, D3DTEXTURE tex) : CObject(vb,tex)
{
	// �A�j���[�V�������쐬
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(1);
	mAnim->isStop = false;
	mAnim->animSpeed = 0.25f;

	isEatAnim = true;
	isWalkAnim = false;
	
}

CGameClearPlayer::~CGameClearPlayer()
{
	CLASS_DELETE(mAnim);
}

void CGameClearPlayer::Update()
{
	if (isWalkAnim == false)
	{
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int> (DIRECTION::LEFT));
		isWalkAnim = true;
	}
	
	if (isEatAnim == false)
	{
		dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(0);
		mAnim->animSpeed = 0.1f;
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayGallEat(static_cast<int> (DIRECTION::LEFT));
		isEatAnim = true;
	}

	CObject::Update();
}

void CGameClearPlayer::Draw()
{
	CObject::Draw();
}
