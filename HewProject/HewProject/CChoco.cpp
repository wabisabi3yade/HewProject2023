#include "CChoco.h"
#include"DoTween.h"
#include"Player.h"

CChoco::CChoco(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	category = Category::FLOOR;
}

CChoco::~CChoco()
{

}

void CChoco::Update()
{
	CGridObject::Update();

}

void CChoco::Draw()
{
	CGridObject::Draw();
}

void CChoco::CRACK()
{
	if (this->type == CGridObject::BlockType::CHOCO)
	{
		this->type = CGridObject::BlockType::CHOCOCRACK;
		this->category = CGridObject::Category::FLOOR;
	}
	else if (this->type == CGridObject::BlockType::CHOCOCRACK)
	{
		//this->BlockType = static_cast <int> (CStageMake::BlockType::HOLL);
		this->SetActive(false);
	};
}
