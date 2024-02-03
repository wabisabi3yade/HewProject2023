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
	CLASS_DELETE(dotween);
}

void CWall::Update()
{
	CGridObject::Update();
	dotween->Update();
}

void CWall::Draw()
{
	CGridObject::Draw();
}

void CWall::Break(float _breakTime)
{
	dotween->DelayedCall(_breakTime, [&]()
		{
			this->SetActive(false); 
		});
}
