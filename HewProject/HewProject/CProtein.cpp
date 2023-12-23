#include "CProtein.h"

CProtein::CProtein(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CProtein::~CProtein()
{
}

void CProtein::Update()
{
	CGridObject::Update();
}

void CProtein::Draw()
{
	CGridObject::Draw();
}
