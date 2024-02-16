#include "CGall.h"
#include"GallAnim.h"
#include"CEffectManeger.h"

CGall::CGall(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	type = BlockType::GALL;
	category = Category::OBJECT;
	playEffect = false;
	mAnim = new GallAnim();
}

CGall::~CGall()
{
	CLASS_DELETE(mAnim);
	for (auto it : effect)
	{
		CLASS_DELETE(it);
		it++;
	}
}

void CGall::Update()
{
	if (!playEffect)
	{
		Vector3 pos = mTransform.pos;
		pos.z += 0.00001f;
		pos.x += 0.0666 * mTransform.scale.x;
		pos.y -= 0.0666 * mTransform.scale.y;
		Vector3 scale = mTransform.scale;
		scale.x *= 1.5f;
		scale.y *= 1.5f;
		CEffect* set = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::BOX, true);
		set->GetEffectAnim()->animSpeed =0.22f;
		effect.push_back(set);
		playEffect = true;
	}
	CGridObject::Update();
	if (effect.size() > 0)
	{
		for (auto it = effect.begin(); it != effect.end(); it++)
		{
			if ((*it)->mTransform.pos.z > this->mTransform.pos.z)
				(*it)->Update();
		}
	}

}

void CGall::Draw()
{
	if (effect.size() > 0)
	{
		for (auto it = effect.begin(); it != effect.end(); it++)
		{
			if ((*it)->mTransform.pos.z > this->mTransform.pos.z)
				(*it)->Draw();
		}
	}
	CGridObject::Draw();
	if (effect.size() > 0)
	{
		for (auto it = effect.begin(); it != effect.end(); it++)
		{
			if ((*it)->mTransform.pos.z < this->mTransform.pos.z)
				(*it)->Draw();
		}
	}
}

void CGall::Open(D3DBUFFER vb ,float _animSpeedRate)
{
	for (auto it : effect)
	{
		CLASS_DELETE(it);
	}
		effect.clear();
	dynamic_cast<GallAnim*>(mAnim)->PlayOpen(_animSpeedRate);
	Vector3 pos = mTransform.pos;
	Vector3 scale = mTransform.scale;
	pos = mTransform.pos;
	pos.z -= 0.00002f;
	pos.x += 0.1206 * mTransform.scale.x;
	pos.y -= 0.0866 * mTransform.scale.y;
	scale = mTransform.scale;
	scale.x *= 0.5f;
	scale.y *= 0.4f;
	CEffect* _set = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::BOX, true);
	_set->GetEffectAnim()->animSpeed = 0.08f;
	effect.push_back(_set);

	pos = mTransform.pos;
	scale = mTransform.scale;

	pos.z -= 0.00003f;
	pos.x += 0.1566 * mTransform.scale.x;
	pos.y += 1.4f * mTransform.scale.y;
	scale.x *= 3.0;
	scale.y *= 3.24f; //1.62
	CEffect* set = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::CLEAR, true);
	set->GetEffectAnim()->animSpeed = 0.45f;
	set->GetEffectAnim()->SetPattern(1);
	set->SetVertexBuffer(vb);
	//set->GetEffectAnim()->animSpeed = 0.08f;
	effect.push_back(set);


}
