#include "CChili.h"

CChili::CChili(D3DBUFFER vb, D3DTEXTURE tex)
	:CItem(vb,tex)
{
	type = BlockType::CHILI;
	category = Category::ITEM;
}

CChili::~CChili()
{
}

void CChili::Update()
{
	CItem::Update();
}

void CChili::Draw()
{
	CItem::Draw();
}
