#include "CCake.h"

CCake::CCake(D3DBUFFER vb, D3DTEXTURE tex)
	:CItem(vb,tex)
{
	type = BlockType::CAKE;
	category = Category::ITEM;
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
