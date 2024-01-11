#include "CCake.h"

CCake::CCake(D3DBUFFER vb, D3DTEXTURE tex)
	:CItem(vb,tex)
{
}

CCake::~CCake()
{
}

void CCake::Update()
{
	CItem::Update();
}

void CCake::Draw()
{
	CItem::Draw();
}
