#include "CArrow.h"

CArrow::CArrow(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb, tex)
{
	dir = NUM;
}

CArrow::~CArrow()
{

}

void CArrow::Update()
{
	mTransform.pos = Owner->mTransform.pos;
	switch (dir)
	{
	case CArrow::DOWN:
		mTransform.pos.x += 0.7f * Owner->mTransform.scale.x;
		mTransform.pos.y -= 0.6f * Owner->mTransform.scale.y;
		break;
	case CArrow::LEFT:
		mTransform.pos.x -= 0.7f * Owner->mTransform.scale.x;
		mTransform.pos.y -= 0.6f * Owner->mTransform.scale.y;
		break;
	case CArrow::RIGHT:
		mTransform.pos.x += 0.7f * Owner->mTransform.scale.x;
		mTransform.pos.y += 0.2f * Owner->mTransform.scale.y;
		break;
	case CArrow::UP:
		mTransform.pos.x -= 0.7f * Owner->mTransform.scale.x;
		mTransform.pos.y += 0.20f * Owner->mTransform.scale.y;
		break;
	default:
		break;
	}
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
	if (_scale != 0)
	{
		Owner->mTransform.scale.x = _scale;
		Owner->mTransform.scale.y = _scale;
	}
	mTransform = Owner->mTransform;
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
