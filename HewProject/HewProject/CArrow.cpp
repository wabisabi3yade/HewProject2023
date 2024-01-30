#include "CArrow.h"

CArrow::CArrow(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb,tex)
{

}

CArrow::~CArrow()
{

}

void CArrow::Update()
{
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

void CArrow::SetOwner(CObject* _owner, DIRECTION _dir)
{
	Owner = _owner;
	switch (_dir)
	{
	case CArrow::DOWN:
		mTransform.pos.y -= ArrowDis;
		break;
	case CArrow::LEFT:
		mTransform.pos.x -= ArrowDis;
		break;
	case CArrow::RIGHT:
		mTransform.pos.x += ArrowDis;
		break;
	case CArrow::UP:
		mTransform.pos.y += ArrowDis;
		break;
	default:
		break;
	}
}
