#include "CGall.h"
#include"CEffectManeger.h"

CGall::CGall(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	type = BlockType::GALL;
	category = Category::OBJECT;
	playEffect = false;

}

CGall::~CGall()
{
	CLASS_DELETE(effect);
}

void CGall::Update()
{
	if (!playEffect)
	{
		Vector3 pos = mTransform.pos;
		pos.z += 0.00001f;
		Vector3 scale = mTransform.scale;
		scale.x *= 1.5f;
		scale.y *= 1.5f;
		effect = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::BOX, true);
		playEffect = true;
	}
	CGridObject::Update();
	if(effect!=nullptr)
	effect->Update();
}

void CGall::Draw()
{
	if(effect!=nullptr)
	effect->Draw();
	CGridObject::Draw();
}
