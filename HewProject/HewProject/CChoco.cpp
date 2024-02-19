#include "CChoco.h"
#include"DoTween.h"
#include"Player.h"
#include"CEffectManeger.h"
#include"xa2.h"
CChoco::CChoco(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	category = Category::FLOOR;
	effect = nullptr;
}

CChoco::~CChoco()
{
	CLASS_DELETE(effect)
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
		CLASS_DELETE(effect);
		effect = EffectManeger::GetInstance()->Play({mTransform.pos.x,mTransform.pos.y,mTransform.pos.z - 0.000001f}, {this->mTransform.scale.x * CRACKSCALE,this->mTransform.scale.y * CRACKSCALE,this->mTransform.scale.z}, EffectManeger::FX_TYPE::CRACK, false);
		XA_Play(SOUND_LABEL::S_CHOCO_BREAK);
		this->type = CGridObject::BlockType::CHOCOCRACK;
		this->category = CGridObject::Category::FLOOR;
	}
	else if (this->type == CGridObject::BlockType::CHOCOCRACK)
	{
		XA_Play(SOUND_LABEL::S_CHOCO_BREAK);
		this->type = CGridObject::BlockType::HOLL;
		this->SetActive(false);
	};
}
