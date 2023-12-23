#include "CGall.h"

CGall::CGall(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CGall::~CGall()
{
}

void CGall::Update()
{
	CGridObject::Update();
}

void CGall::Draw()
{
	CGridObject::Draw();
}
