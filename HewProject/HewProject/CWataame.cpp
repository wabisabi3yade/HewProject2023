#include "CWataame.h"
CWataame::CWataame(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CWataame::~CWataame()
{
}

void CWataame::Update()
{
	CGridObject::Update();
}

void CWataame::Draw()
{
	CGridObject::Draw();
}

void CWataame::Melt()
{
	//this->SetBlookType(static_cast<int>(CStageMake::BlockType::HOLL));
	this->SetActive(false);
}
