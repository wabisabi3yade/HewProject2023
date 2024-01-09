#include "CChoco.h"
#include"CStageMake.h"
#include"DoTween.h"
#include"Player.h"

CChoco::CChoco(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{

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
	if (this->BlockType == static_cast<int>(CStageMake::BlockType::CHOCO))
	{
		this->BlockType = static_cast <int> (CStageMake::BlockType::CHOCOCRACK);
		this->category = static_cast<int> (CStageMake::Category::FLOOR);
	}
	else if (this->BlockType == static_cast<int>(CStageMake::BlockType::CHOCOCRACK))
	{
		this->BlockType = static_cast <int> (CStageMake::BlockType::HOLL);
		this->SetActive(false);
	};
}
