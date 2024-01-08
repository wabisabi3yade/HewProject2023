#include "CWall.h"
#include "DoTween.h"
#include"Player.h"
CWall::CWall(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	dotween = new DoTween(this);
}
CWall::~CWall()
{
}

void CWall::Update()
{
	CGridObject::Update();
}

void CWall::Draw()
{
	CGridObject::Draw();
}

void CWall::Break()
{
	dotween->DelayedCall(3.0f, [&]()
		{isActive = false; });
}
