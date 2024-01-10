#include "CCoin.h"

CCoin::CCoin(D3DBUFFER vb, D3DTEXTURE tex)
	:CItem(vb, tex)
{
}

CCoin::~CCoin()
{
}

void CCoin::Update()
{
	CItem::Update();
}

void CCoin::Draw()
{
	CItem::Draw();
}
