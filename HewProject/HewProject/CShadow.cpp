#include "CShadow.h"

CShadow::CShadow(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
}

CShadow::~CShadow()
{
}

void CShadow::Update()
{
	CObject::Update();
}

void CShadow::Draw()
{
	CObject::Draw();
}
