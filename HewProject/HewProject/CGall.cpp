#include "CGall.h"
#include"GallAnim.h"
#include"CEffectManeger.h"
#include"DoTween.h"
#include"Player.h"
CGall::CGall(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	type = BlockType::GALL;
	category = Category::OBJECT;
	playEffect = false;
	mAnim = new GallAnim();
	dotween = std::make_unique<DoTween>(this);

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
		//Vector3 pos = mTransform.pos;
		//pos.z -= 0.00001f;
		//pos.x += 0.0666 * mTransform.scale.x;
		//pos.y -= 0.0666 * mTransform.scale.y;
		//Vector3 scale = mTransform.scale;
		//scale.x *= 1.5f;
		//scale.y *= 1.5f;
		//CEffect* set = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::BOX, true);
		//set->GetEffectAnim()->animSpeed = 0.22f;
		//set->SetAlpha(0.5f);
		//effect.push_back(set);
		o_Transform = mTransform;
		mTransform.scale.x *= 1.5f;
		mTransform.scale.y *= 1.5f;
		mTransform.pos.x += 0.35f;
		mTransform.pos.y -= 0.3f;
		playEffect = true;
	}
	dotween->Update();
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

void CGall::Open(D3DBUFFER vb, float _animSpeedRate, float _scale)
{
	for (auto it : effect)
	{
		CLASS_DELETE(it);
	}
	effect.clear();
	dynamic_cast<GallAnim*>(mAnim)->PlayOpen(_animSpeedRate);

	mTransform = o_Transform;

	mTransform.pos.y -= 0.03f* mTransform.scale.y;
	dotween->DelayedCall(BREAK_TIME / 2.0f, [&,vb,_animSpeedRate,_scale]()
		{
			Vector3 pos = mTransform.pos;
			Vector3 scale = mTransform.scale;

			pos.z -= 0.00003f;
			pos.x += 0.1566 * mTransform.scale.x * _scale;
			pos.y += 1.4f * mTransform.scale.y * _scale;
			scale.x *= 3.0 * _scale;
			scale.y *= 3.24f * _scale; //1.62
			CEffect* set = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::CLEAR, true);
			set->GetEffectAnim()->animSpeed = 0.45f;
			set->GetEffectAnim()->SetPattern(1);
			set->SetVertexBuffer(vb);
			//set->GetEffectAnim()->animSpeed = 0.08f;
			effect.push_back(set);
		});

}
