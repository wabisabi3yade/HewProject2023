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
	// �����ɍs���Ƃ��̍s���̏���
	// �@ ISOME_BACKMOVE�����@�i��������́��ɂ���I�u�W�F�N�g��艜�Ɉړ�����̂ŃI�u�W�F�N�g��艜�ɂ���j
	// �A�ړ���ɓ�������Ƃ��̏��ɍ��킹��Z���W�ɍ��킹��
	if (_dir == static_cast<int>(Player::DIRECTION::UP) || _dir == static_cast<int>(Player::DIRECTION::RIGHT))
	{
		mTransform.pos.z += ISOME_BACKMOVE;
	}
	// ��O�̃}�X�ɍs���Ƃ��͐��Z���W����O�ɍ��킹��
	else
	{
		mTransform.pos.z = _pos.z + 0.001f;
	}

	dotween->DoMoveXY({ _pos.x,_pos.y }, CASTELLAWALK_TIME);
	dotween->Append(_pos.z, 0.0f, DoTween::FUNC::MOVE_Z);

	// ���ɗ�����̂Ȃ�
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
