#include "CProtein.h"

CProtein::CProtein(D3DBUFFER vb, D3DTEXTURE tex)
	:CItem(vb,tex)
{

}

CProtein::~CProtein()
{
	
}

void CProtein::Update()
{
	CItem::Update();
}

void CProtein::Draw()
{
	CItem::Draw();
}
