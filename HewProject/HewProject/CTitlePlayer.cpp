#include "CTitlePlayer.h"
#include"CPlayerAnim.h"
#include <random>

#define MAX_POSITION_X 9
#define MIN_POSITION_X -9

#define MAX_POSITION_Y 5
#define MIN_POSITION_Y -5

#define PLAYER_POSZ (-0.1f)

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_real_distribution<float> distr(MIN_POSITION_Y, MAX_POSITION_Y);

CTitlePlayer::CTitlePlayer(D3DBUFFER vb, D3DTEXTURE tex) :CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);

	//アニメーションを作成
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(1);
	mAnim->isStop = false;
	mAnim->animSpeed = 2.0f;

	mTransform.pos = { 7.0f,distr(eng),PLAYER_POSZ };

	nRandomChara = 0;
	nAction = 0;
	isNormal = false;
	isStopMove = false;
}

CTitlePlayer::~CTitlePlayer()
{
	CLASS_DELETE(mAnim);
}

void CTitlePlayer::Update()
{
	if (isNormal == false)
	{
		isNormal = true;

		switch (nAction)
		{
		case 0:
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			dotween->DoMoveX(MIN_POSITION_X, 2.0f);
			dotween->OnComplete([&]() {
				isNormal = false;
				isStopMove = true;
				mTransform.pos = { distr(eng),MAX_POSITION_Y - 0.1f,PLAYER_POSZ };
				});
			break;
		case 1:
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			dotween->DoMoveXY({ MIN_POSITION_X,MIN_POSITION_Y }, 2.0f);
			dotween->OnComplete([&]() {
				isNormal = false;
				isStopMove = true;
				mTransform.pos = { MIN_POSITION_X + 0.1f,distr(eng),PLAYER_POSZ};
				});
			break;
		case 2:
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			dotween->DoMoveY(MIN_POSITION_Y, 2.0f);
			dotween->OnComplete([&]() {
				isNormal = false;
				isStopMove = true;
				mTransform.pos = { distr(eng),MIN_POSITION_Y + 0.1f,PLAYER_POSZ };
				});
			break;
		case 3:
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			dotween->DoMoveXY({MAX_POSITION_X,distr(eng)}, 2.0f);
			dotween->OnComplete([&]() {
				isNormal = false;
				isStopMove = true;
				mTransform.pos = { MAX_POSITION_X - 0.1f,distr(eng),PLAYER_POSZ};
				});
			break;
		default:
			break;
		}
		
	}
	
	dotween->Update();
	CObject::Update();
}

void CTitlePlayer::Draw()
{
	CObject::Draw();
}
