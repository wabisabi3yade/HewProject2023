#include "CTitlePlayer.h"
#include"CPlayerAnim.h"

CTitlePlayer::CTitlePlayer(D3DBUFFER vb, D3DTEXTURE tex) :CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);

	//アニメーションを作成
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(1);
	mAnim->isStop = false;
}

CTitlePlayer::~CTitlePlayer()
{
	CLASS_DELETE(mAnim);
}

void CTitlePlayer::Update()
{
	dotween->Update();
	CObject::Update();
}

void CTitlePlayer::Draw()
{
	CObject::Draw();
}
