#include "CChoco.h"
#include"DoTween.h"
#include"Player.h"
#include"CEffectManeger.h"
CChoco::CChoco(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	category = Category::FLOOR;
	effectMane = nullptr;
	effect = nullptr;
}

CChoco::~CChoco()
{

}

void CChoco::Update()
{
	if (effect != nullptr)
	{
		effect->Update();
	}
	CGridObject::Update();
}

void CChoco::Draw()
{
	CGridObject::Draw();
	if (effect != nullptr)
	{
		effect->Draw();
	}
}

void CChoco::CRACK()
{
	if (this->type == CGridObject::BlockType::CHOCO)
	{
		effectMane = EffectManeger::GetInstance();
		CLASS_DELETE(effect);
		effect = effectMane->Play({ mTransform.pos.x,mTransform.pos.y,mTransform.pos.z - 0.000001f }, { this->mTransform.scale.x * CRACKSCALE,this->mTransform.scale.y * CRACKSCALE,this->mTransform.scale.z }, EffectManeger::FX_TYPE::CRACK, false);
		this->type = CGridObject::BlockType::CHOCOCRACK;
		this->category = CGridObject::Category::FLOOR;
	}
	else if (this->type == CGridObject::BlockType::CHOCOCRACK)
	{
		this->type = CGridObject::BlockType::HOLL;
		this->SetActive(false);
	};
}
