#include "CGumi.h"

CGumi::CGumi(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CGumi::~CGumi()
{
}

void CGumi::Update()
{
	CGridObject::Update();
}

void CGumi::Draw()
{
	CGridObject::Draw();
}
