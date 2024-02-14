#include "CWataame.h"
#include"DoTween.h"
#include"Player.h"
#include"CEffectManeger.h"
CWataame::CWataame(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	dotween = std::make_unique<DoTween>(this);
}

CWataame::~CWataame()
{
	CLASS_DELETE(effect);
}

void CWataame::Update()
{
	dotween->Update();
	CGridObject::Update();
	if (effect != nullptr)
		effect->Draw();
}

void CWataame::Draw()
{
	if (effect != nullptr)
		effect->Draw();
	CGridObject::Draw();
}

void CWataame::Melt()
{
	dotween->DoDelay(WALK_TIME);
	dotween->Append({0.0f,0.0f,1.0f}, MELT_TIME, DoTween::FUNC::SCALE);
	Vector3 pos = this->mTransform.pos;
	Vector3 scale = this->mTransform.scale;
	pos.z -= 0.00001f;
	pos.y += scale.y / 3.0f;
	scale.x *= KUMO_SCALE;
	scale.y *= KUMO_SCALE;

	dotween->OnComplete([&,pos,scale]()
		{
			effect = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::KUMO, false);
			this->SetActive(false);
		});
}
