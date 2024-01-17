#include "CChili.h"

CChili::CChili(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	type = BlockType::CHILI;
	category = Category::ITEM;
}

CChili::~CChili()
{
}

void CChili::Update()
{
	CGridObject::Update();
}

void CChili::Draw()
{
	CGridObject::Draw();
}
