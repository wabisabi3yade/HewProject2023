#include "CWall.h"
#include "DoTween.h"
#include"Player.h"
//#include"CStageMake.h"
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

void CWall::Break()
{
	dotween->DelayedCall(BREAK_TIME, [&]()
		{
			this->SetActive(false); 
		});
}
