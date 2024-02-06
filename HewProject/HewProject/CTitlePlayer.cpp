#include "CTitlePlayer.h"
#include"CPlayerAnim.h"
#include <random>

#define MAX_POSITION_X 10
#define MIN_POSITION_X -10

#define MAX_POSITION_Y 6
#define MIN_POSITION_Y -6

#define PLAYER_POSZ (-0.1f)

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_real_distribution<float> distr_Y(MIN_POSITION_Y, MAX_POSITION_Y);
std::uniform_real_distribution<float> distr_X(MIN_POSITION_X, MAX_POSITION_X);

CTitlePlayer::CTitlePlayer(D3DBUFFER vb, D3DTEXTURE tex) :CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);

	//アニメーションを作成
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(1);
	mAnim->isStop = false;
	mAnim->animSpeed = 0.1f;

	mTransform.pos = { 7.0f,distr_Y(eng),PLAYER_POSZ };

	nRandomChara = 0;
	nAction = 0;
	isNormal = false;
	isFat = false;
	isThin = false;
	isAll = false;
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
		Vector2 target = Vector2::zero;
		Vector2 charPos = Vector2::zero;
		Vector2 vec = Vector2::zero; 

		switch (nAction)
		{
		case 0:

			target = { MIN_POSITION_X, distr_Y(eng) };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.y >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::UP));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			}
			dotween->DoMoveXY(target, 2.0f);
			dotween->OnComplete([&]() {
				isNormal = false;
				isStopMove = true;
				mTransform.pos = { distr_X(eng),MAX_POSITION_Y + 0.1f,PLAYER_POSZ };
				});
			break;
		case 1:
			target = { distr_X(eng), MAX_POSITION_Y };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.x >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::RIGHT));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::UP));
			}
			dotween->DoMoveXY(target, 2.0f);
			dotween->OnComplete([&]() {
				isNormal = false;
				isStopMove = true;
				mTransform.pos = { MIN_POSITION_X + 0.1f,distr_Y(eng),PLAYER_POSZ };
				});
			break;
		case 2:
			target = { distr_X(eng), MIN_POSITION_Y };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;

			if (vec.x >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			}
			dotween->DoMoveXY(target, 2.0f);
			dotween->OnComplete([&]() {
				isNormal = false;
				isStopMove = true;
				mTransform.pos = { distr_X(eng),MIN_POSITION_Y + 0.1f,PLAYER_POSZ };
				});
			break;
		case 3:
			target = { MAX_POSITION_X, distr_Y(eng) };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;

			if (vec.y >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::RIGHT));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			}
			dotween->DoMoveXY(target, 2.0f);
			dotween->OnComplete([&]() {
				isNormal = false;
				isStopMove = true;
				mTransform.pos = { MAX_POSITION_X - 0.1f,distr_Y(eng),PLAYER_POSZ };
				});
			break;
		default:
			break;
		}

	}
	else if(isFat == false)
	{
		isFat = true;
		Vector2 target = Vector2::zero;
		Vector2 charPos = Vector2::zero;
		Vector2 vec = Vector2::zero;

		mAnim->animSpeed = 0.2f;

		switch (nAction)
		{
		case 0:
			target = { distr_X(eng), MIN_POSITION_Y};
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.x >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			}
			dotween->DoMoveXY(target, 3.0f);
			dotween->OnComplete([&]() {
				isFat = false;
				isStopMove = true;
				mTransform.pos = { distr_X(eng),MIN_POSITION_Y + 0.1f,PLAYER_POSZ - 0.01f };
				});
			break;
		case 1:
			target = { MIN_POSITION_X, distr_Y(eng) };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.y >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::UP));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			}
			dotween->DoMoveXY(target, 3.0f);
			dotween->OnComplete([&]() {
				isFat = false;
				isStopMove = true;
				mTransform.pos = { MIN_POSITION_X + 0.1f,distr_Y(eng),PLAYER_POSZ - 0.01f };
				});
			break;
		case 2:
			target = { distr_X(eng), MAX_POSITION_Y };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.x >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::RIGHT));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::UP));
			}
			dotween->DoMoveXY(target, 3.0f);
			dotween->OnComplete([&]() {
				isFat = false;
				isStopMove = true;
				mTransform.pos = { distr_X(eng),MAX_POSITION_Y + 0.1f,PLAYER_POSZ - 0.01f };
				});
			break;
		case 3:
			target = { MAX_POSITION_X, distr_Y(eng) };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;

			if (vec.y >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::RIGHT));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			}
			dotween->DoMoveXY( target, 3.0f);
			dotween->OnComplete([&]() {
				isFat = false;
				isStopMove = true;
				mTransform.pos = { MAX_POSITION_X - 0.1f,distr_Y(eng),PLAYER_POSZ - 0.01f };
				});
			break;
		default:
			break;
		}
	}
	else if(isThin == false)
	{
		isThin = true;
		Vector2 target = Vector2::zero;
		Vector2 charPos = Vector2::zero;
		Vector2 vec = Vector2::zero;

		mAnim->animSpeed = 0.3f;

		switch (nAction)
		{
		case 0:
			target = { distr_X(eng), MAX_POSITION_Y };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.x >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::RIGHT));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::UP));
			}
			dotween->DoMoveXY(target, 4.0f);
			dotween->OnComplete([&]() {
				isThin = false;
				isStopMove = true;
				mTransform.pos = { distr_X(eng),MAX_POSITION_Y + 0.1f,PLAYER_POSZ - 0.02f };
				});
			break;
		case 1:
			target = { MIN_POSITION_X, distr_Y(eng) };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.y >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::UP));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			}
			dotween->DoMoveXY(target, 4.0f);
			dotween->OnComplete([&]() {
				isThin = false;
				isStopMove = true;
				mTransform.pos = { MIN_POSITION_X + 0.1f,distr_Y(eng),PLAYER_POSZ - 0.02f };
				});
			break;
		case 2:

			target = { distr_X(eng), MIN_POSITION_Y };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.x >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			}
			
			dotween->DoMoveXY(target, 4.0f);
			dotween->OnComplete([&]() {
				isThin = false;
				isStopMove = true;
				mTransform.pos = { distr_X(eng),MIN_POSITION_Y + 0.1f,PLAYER_POSZ - 0.02f };
				});
			break;
		case 3:
			target = { MAX_POSITION_X, distr_Y(eng) };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;

			if (vec.y >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::RIGHT));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			}
			dotween->DoMoveXY(target, 4.0f);
			dotween->OnComplete([&]() {
				isThin = false;
				isStopMove = true;
				mTransform.pos = { MAX_POSITION_X - 0.1f,distr_Y(eng),PLAYER_POSZ - 0.02f };
				});
			break;
		default:
			break;
		}
	}
	else if (isAll == false)
	{
		isAll = true;
		Vector2 target = Vector2::zero;
		Vector2 charPos = Vector2::zero;
		Vector2 vec = Vector2::zero;

		mAnim->animSpeed = 0.4f;

		switch (nAction)
		{
		case 0:
			target = { MAX_POSITION_X, distr_Y(eng) };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;

			if (vec.y >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::RIGHT));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			}
			dotween->DoMoveXY(target, 5.0f);
			dotween->OnComplete([&]() {
				isAll = false;
				isStopMove = true;
				mTransform.pos = { MAX_POSITION_X,distr_Y(eng) + 0.1f,PLAYER_POSZ - 0.03f};
				});
			break;
		case 1:
			target = { MIN_POSITION_X, distr_Y(eng) };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.y >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::UP));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			}
			dotween->DoMoveXY(target, 5.0f);
			dotween->OnComplete([&]() {
				isAll = false;
				isStopMove = true;
				mTransform.pos = { MIN_POSITION_X + 0.1f,distr_Y(eng),PLAYER_POSZ - 0.03f };
				});
			break;
		case 2:

			target = { distr_X(eng), MIN_POSITION_Y };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.x >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::DOWN));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::LEFT));
			}
			
			dotween->DoMoveXY(target, 5.0f);
			dotween->OnComplete([&]() {
				isAll = false;
				isStopMove = true;
				mTransform.pos = { distr_X(eng),MIN_POSITION_Y + 0.1f,PLAYER_POSZ - 0.03f };
				});
			break;
		case 3:
			target = { distr_X(eng), MAX_POSITION_Y };
			charPos = { mTransform.pos.x, mTransform.pos.y };
			vec = target - charPos;
			if (vec.x >= 0)
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::RIGHT));
			}
			else
			{
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(DIRECTION::UP));
			}
			dotween->DoMoveXY({ distr_X(eng),MAX_POSITION_Y}, 5.0f);
			dotween->OnComplete([&]() {
				isAll = false;
				isStopMove = true;
				mTransform.pos = { MAX_POSITION_X - 0.1f,distr_Y(eng),PLAYER_POSZ - 0.03f };
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
