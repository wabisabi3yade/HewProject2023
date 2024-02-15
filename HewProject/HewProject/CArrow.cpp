#include "CArrow.h"
#include"DoTween.h"
#include"Player.h"
constexpr float ARROW_SCALEUP_TIME = 0.8f;
constexpr float ARROW_WAIT_TIME = 0.8f;

CArrow::CArrow(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb, tex)
{
	dir = NUM;
	dotween = std::make_unique<DoTween>(this);
	scaleUpVal = Vector3::zero;
	scaleDownVal = Vector3::zero;
}

CArrow::~CArrow()
{

}

void CArrow::Update()
{
	mTransform.pos = Owner->mTransform.pos;
	if (dynamic_cast<Player*>(Owner)->GetState() == Player::STATE::MUSCLE)
	{
		mTransform.pos.y /= 1.5f;
	}
	switch (dir)
	{
	case CArrow::DOWN:
		mTransform.pos.x += 0.7f * stageScale;
		mTransform.pos.y -= 0.6f * stageScale;
		break;
	case CArrow::LEFT:
		mTransform.pos.x -= 0.7f * stageScale;
		mTransform.pos.y -= 0.6f * stageScale;
		break;
	case CArrow::RIGHT:
		mTransform.pos.x += 0.7f * stageScale;
		mTransform.pos.y += 0.2f * stageScale;
		break;
	case CArrow::UP:
		mTransform.pos.x -= 0.7f * stageScale;
		mTransform.pos.y += 0.20f * stageScale;
		break;
	default:
		break;
	}
	dotween->Update();
	CObject::Update();
}

void CArrow::Draw()
{
	CObject::Draw();
}

void CArrow::SetArrow(D3DTEXTURE _tex)
{
	mTexture = _tex;

}

void CArrow::SetOwner(CObject* _owner, DIRECTION _dir, float _scale)
{
	Owner = _owner;
	stageScale = _scale;
	mTransform = Owner->mTransform;
	mTransform.scale.x = _scale;
	mTransform.scale.y = _scale;

	mTransform.scale.x *= 0.4f;
	mTransform.scale.y *= 0.4f;
	dir = _dir;
	switch (_dir)
	{
	case CArrow::DOWN:
		mTransform.pos.x -= 0.5f * mTransform.scale.x;
		mTransform.pos.y -= 0.5f * mTransform.scale.y;
		mTransform.rotation.z = 220.0f;
		break;
	case CArrow::LEFT:
		mTransform.pos.x -= 0.2f * mTransform.scale.x;
		mTransform.pos.y += 0.2f * mTransform.scale.y;
		mTransform.rotation.z = 140.0f;
		break;
	case CArrow::RIGHT:
		mTransform.pos.x += 0.2f * mTransform.scale.x;
		mTransform.pos.y -= 0.2f * mTransform.scale.y;
		mTransform.rotation.z = 325.0f;
		break;
	case CArrow::UP:
		mTransform.pos.x -= 0.2f * mTransform.scale.x;
		mTransform.pos.y += 0.2f * mTransform.scale.y;
		mTransform.rotation.z = 45.0f;
		break;
	default:
		break;
	}
}

void CArrow::ScaleLoop()
{
	mTransform.scale.x = Owner->mTransform.scale.x * 0.4f;
	mTransform.scale.y = Owner->mTransform.scale.y * 0.4f;
	scaleDownVal = mTransform.scale;
	scaleUpVal = mTransform.scale;
	scaleUpVal.x *= 1.3f;
	scaleUpVal.y *= 1.3f;
	dotween->DoScale(scaleUpVal, ARROW_SCALEUP_TIME);
	dotween->Append(scaleDownVal, ARROW_SCALEUP_TIME, DoTween::FUNC::SCALE);
	dotween->Append(Vector3::zero, ARROW_WAIT_TIME, DoTween::FUNC::DELAY);
	dotween->SetLoop(-1);
}
