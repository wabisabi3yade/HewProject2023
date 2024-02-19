#include "CWall.h"
#include "DoTween.h"
#include"Player.h"
#include"CEffectManeger.h"

constexpr float dis_X = 0.3f;
constexpr float dis_Y = 0.3f;

CWall::CWall(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	dotween = new DoTween(this);
	isBreak = false;
	isDecrease = false;
	time = 0;
}
CWall::~CWall()
{
	CLASS_DELETE(dotween);
	CLASS_DELETE(effect);
}

void CWall::Update()
{
	CGridObject::Update();
	dotween->Update();
	if (isBreak)
	{
		time += 1.0f / 60.0;
		static short c_time = 0;
		static short o_time = 0;
		c_time = static_cast<UINT>(time / 0.1f);
		if (c_time != o_time)
		{
			this->ChangeInvisible();
		}
		o_time = c_time;
	}
	if (isDecrease)
	{
		this->materialDiffuse.w -= 0.01f;
	}
	if (effect != nullptr)
		effect->Update();
}

void CWall::Draw()
{
	if (effect != nullptr)
	if(effect->mTransform.pos.z  > this->mTransform.pos.z)
	effect->Draw();
	CGridObject::Draw();
	if (effect != nullptr)
		if(effect->mTransform.pos.z  < this->mTransform.pos.z)
		effect->Draw();
}

void CWall::Break(int _dir, float _breakTime)
{
	Vector3 pos = this->mTransform.pos;
	Vector3 scale = this->mTransform.scale;
	scale.x *= PANTI_SCALE;
	scale.y *= PANTI_SCALE;
	switch (_dir)
	{
	case 0:
		pos.x -= dis_X * this->mTransform.scale.x;
		pos.y += dis_Y * this->mTransform.scale.y;
		pos.z += 0.0001f;
		break;
	case 1:
		pos.x += dis_X * this->mTransform.scale.x;
		pos.y += dis_Y * this->mTransform.scale.y;
		pos.z += 0.0001f;
		break;
	case 2:
		pos.x -= dis_X * this->mTransform.scale.x/3.0f;
		pos.y += dis_Y * this->mTransform.scale.y;
		pos.z -= 0.0001f;
		break;
	case 3:
		pos.x += dis_X * this->mTransform.scale.x;
		pos.y += dis_Y * this->mTransform.scale.y;
		pos.z -= 0.0001f;
		break;
	default:
		break;
	}
	dotween->DelayedCall(_breakTime / 2.0, [&,pos,scale,_dir]()
		{
			isBreak = true;
			time = 0;
			isDecrease = true;
			if( _dir == 1 || _dir == 2)
			effect = EffectManeger::GetInstance()->Play(pos,scale,EffectManeger::FX_TYPE::PANTI_L,false);
			else if(_dir == 0 || _dir == 3 )
			effect = EffectManeger::GetInstance()->Play(pos,scale,EffectManeger::FX_TYPE::PANTI,false);
		});
	dotween->DelayedCall(_breakTime, [&]()
		{
			isBreak = false;
			this->SetActive(false);
		});
}
