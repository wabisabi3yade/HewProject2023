#include "CFade.h"
#include"DoTween.h"

#define TIME_FADE (1.0f)	// �t�F�[�h�C���ɂ����鎞��
#define TIME_FADEOUT (1.0f)	// �t�F�[�h�A�E�g�ɂ����鎞��

void CFade::FadeIn(FadeType _fadeType)
{
	if (fadeState != FadeState::NO_FADE)
	{
		return;
	}
	fadeState = FadeState::FADE_IN;
	fadeType = _fadeType;
	switch (fadeType)
	{
	case CFade::DEFAULT:
		mTransform.pos = Vector3::zero;
		break;
	case CFade::LEFT:
		mTransform.pos = Vector3::zero + mTransform.scale.x / 2;
		doTween->DoMoveX(0.0f, TIME_FADE);
		break;
	case CFade::RIGHT:
		mTransform.pos = Vector3::zero - mTransform.scale.x;
		doTween->DoMoveX(0.0f, TIME_FADE);
		break;
	case CFade::UP:
		mTransform.pos = Vector3::zero - mTransform.scale.y;
		doTween->DoMoveX(0.0f, TIME_FADE);
		break;
	case CFade::DOWN:
		mTransform.pos = Vector3::zero + mTransform.scale.y;
		doTween->DoMoveX(0.0f, TIME_FADE);
		break;
	case CFade::TO_TOP_LEFT:
		mTransform.pos = Vector3(Vector3::zero.x + mTransform.scale.x, Vector3::zero.y - mTransform.scale.y, Vector3::zero.z);
		doTween->DoMove(Vector3::zero, TIME_FADE);
		break;
	case CFade::TO_TOP_RIGHT:
		mTransform.pos = Vector3(Vector3::zero.x - mTransform.scale.x, Vector3::zero.y - mTransform.scale.y, Vector3::zero.z);
		doTween->DoMove(Vector3::zero, TIME_FADE);
		break;
	case CFade::TO_BOTTOM_LEFT:
		mTransform.pos = Vector3(Vector3::zero.x + mTransform.scale.x, Vector3::zero.y + mTransform.scale.y, Vector3::zero.z);
		doTween->DoMove(Vector3::zero, TIME_FADE);
		break;
	case CFade::TO_BOTTOM_RIGHT:
		mTransform.pos = Vector3(Vector3::zero.x - mTransform.scale.x, Vector3::zero.y + mTransform.scale.y, Vector3::zero.z);
		doTween->DoMove(Vector3::zero, TIME_FADE);
		break;

	default:
		break;
	}
}

void CFade::FadeOut(FadeType _fadeType)
{
	if (fadeState != FadeState::NO_FADE)
	{
		return;
	}
	fadeState = FadeState::FADE_OUT;

	mTransform.pos = Vector3::zero;	// �ŏ��Ɍ��_�փt�F�[�h���ړ�������
	switch (fadeType)
	{
	case CFade::DEFAULT:
		break;

	case CFade::LEFT:
		doTween->DoMoveX(-mTransform.scale.x, TIME_FADEOUT);
		break;

	case CFade::RIGHT:
		doTween->DoMoveX(mTransform.scale.x, TIME_FADEOUT);
		break;

	case CFade::UP:
		doTween->DoMoveY(mTransform.scale.y, TIME_FADEOUT);
		break;

	case CFade::DOWN:
			doTween->DoMoveY(-mTransform.scale.y, TIME_FADEOUT);
			break;

		case CFade::TO_TOP_LEFT:
			doTween->DoMove({ -mTransform.scale.x, mTransform.scale.y, 0 }, TIME_FADEOUT);
			break;

		case CFade::TO_TOP_RIGHT:
			doTween->DoMove({ mTransform.scale.x, mTransform.scale.y, 0 }, TIME_FADEOUT);
			break;

		case CFade::TO_BOTTOM_LEFT:
			doTween->DoMove({ -mTransform.scale.x, -mTransform.scale.y, 0 }, TIME_FADEOUT);
			break;

		case CFade::TO_BOTTOM_RIGHT:
			doTween->DoMove({ mTransform.scale.x, -mTransform.scale.y, 0 }, TIME_FADEOUT);
			break;

		default:
			break;
	}
}

CFade::CFade(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	doTween = new DoTween(this);
}

CFade::~CFade()
{
	CLASS_DELETE(doTween);
}

void CFade::Draw()
{
	CObject::Draw();
}

void CFade::Update()
{
	if (fadeState == FadeState::FADE_IN)
	{
		//�t�F�[�h�p�|���S���𓧖��ɂ��Ă���
		materialDiffuse.w -= 0.01f;

		//���S�ɓ����ɂȂ�����
		if (materialDiffuse.w <= 0.0f)
		{
			fadeState = FadeState::NO_FADE;
			isActive = false;
		}
	}
	else if (fadeState == FadeState::FADE_OUT)
	{
		//�t�F�[�h�p�|���S����s�����ɂ��Ă���
		materialDiffuse.w += 0.01f;


		//���S�ɕs�����ɂȂ�����
		if (materialDiffuse.w >= 1.0f)
		{
			//�V�[���؂�ւ��̊֐��@�K�v
			fadeState = FadeState::NO_FADE;
			//SetScene(newScene);
		}
	}
	if (fadeState != FadeState::NO_FADE)
	{
		doTween->Update();
	}
	CObject::Update();
}
