#include "CGumi.h"

CGumi::CGumi(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	type = BlockType::GUMI;
	category = Category::OBJECT;
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
