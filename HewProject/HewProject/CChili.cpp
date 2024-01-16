#include "CChili.h"

CChili::CChili(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	dotween = new DoTween(this);
}

CChili::~CChili()
{
	CLASS_DELETE(dotween);
}

void CChili::Update()
{
	CGridObject::Update();
	dotween->Update();
}

void CChili::Draw()
{
	CGridObject::Draw();
}
