#include "CCastella.h"
#include "Player.h"
#include "CEffectManeger.h"
#include "xa2.h"

CCastella::CCastella(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);
}

CCastella::~CCastella()
{
	CLASS_DELETE(effect);
}

void CCastella::Update()
{
	if (effect != nullptr)
		effect->Update();
	CGridObject::Update();
	dotween->Update();
	mTransform.pos;
}

void CCastella::Move(Vector3 _pos, int _dir, Vector3 _fallPos)
{
	// 奥側に行くときの行動の順番
	// ① ISOME_BACKMOVE足す　（同じ横列の↑にあるオブジェクトより奥に移動するのでオブジェクトより奥にする）
	// ②移動先に到着するとその床に合わせたZ座標に合わせる
	if (_dir == static_cast<int>(Player::DIRECTION::UP) || _dir == static_cast<int>(Player::DIRECTION::RIGHT))
	{
		mTransform.pos.z += ISOME_BACKMOVE;
	}
	// 手前のマスに行くときは先にZ座標を手前に合わせる
	else
	{
		mTransform.pos.z = _pos.z + 0.001f;
	}

	dotween->DoMoveXY({ _pos.x,_pos.y }, CASTELLAWALK_TIME);
	dotween->Append(_pos.z, 0.0f, DoTween::FUNC::MOVE_Z);

	// 床に落ちるのなら
	if (_fallPos != Vector3::zero)
	{
		dotween->Append(_fallPos.z, 0.0f, DoTween::FUNC::MOVE_Z);
		dotween->Append(_fallPos, CASTELLAFALL_TIME, DoTween::FUNC::MOVE_XY);
		Vector3 pos = _fallPos;
		Vector3 scale = this->mTransform.scale;
		pos.z -=  0.000001f;
		scale.x *= STAR_CASTELLA_SCALE;
		scale.y *= STAR_CASTELLA_SCALE;
		pos.y += 0.3f * this->mTransform.scale.y;
		dotween->OnComplete([&, pos, scale]()
			{
				effect = EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::STAR_CASTELLA, false);

				XA_Play(SOUND_LABEL::S_INCANNON);
			});
	}


}

void CCastella::Draw()
{
	CGridObject::Draw();
	if (effect != nullptr)
		effect->Draw();
}
