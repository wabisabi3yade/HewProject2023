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
		Vector3 pos = mTransform.pos;
		pos.z -= 0.000001f;
		Vector3 scale = mTransform.scale;
		scale.x *= CRACKSCALE;
		scale.y *= CRACKSCALE;
		effect = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::CRACK, false);
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
