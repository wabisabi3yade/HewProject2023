#include "CFade.h"
#include"DoTween.h"

void CFade::FadeIn(FadeType _fadeType)
{
	fadeState = FadeState::FADE_IN;
	fadeType = _fadeType;
	switch (fadeType)
	{
	case CFade::DEFAULT:
		mTransform.pos = Vector3::zero;
		break;
	case CFade::LEFT:
		mTransform.pos = Vector3::zero + mTransform.scale.x/2;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::LEFT);
		break;
	case CFade::RIGHT:
		mTransform.pos = Vector3::zero - mTransform.scale.x;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::RIGHT);
		break;
	case CFade::UP:
		mTransform.pos = Vector3::zero - mTransform.scale.y;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::UP);
		break;
	case CFade::DOWN:
		mTransform.pos = Vector3::zero + mTransform.scale.y;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::DOWN);
		break;
	default:
		break;
	}
}

void CFade::FadeOut()
{
	fadeState = FadeState::FADE_OUT;
	switch (fadeType)
	{
	case CFade::DEFAULT:
		mTransform.pos = Vector3::zero;
		break;
	case CFade::LEFT:
		mTransform.pos = Vector3::zero + mTransform.scale.x;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::LEFT);
		break;
	case CFade::RIGHT:
		mTransform.pos = Vector3::zero - mTransform.scale.x;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::RIGHT);
		break;
	case CFade::UP:
		mTransform.pos = Vector3::zero - mTransform.scale.y;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::UP);
		break;
	case CFade::DOWN:
		mTransform.pos = Vector3::zero + mTransform.scale.y;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::DOWN);
		break;
	default:
		break;
	}
}

void CFade::FadeOut(FadeType _fadeType)
{
	fadeState = FadeState::FADE_OUT;
	fadeType = _fadeType;
	switch (fadeType)
	{
	case CFade::DEFAULT:
		mTransform.pos = Vector3::zero;
		break;
	case CFade::LEFT:
		mTransform.pos = Vector3::zero + mTransform.scale.x;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::LEFT);
		break;
	case CFade::RIGHT:
		mTransform.pos = Vector3::zero - mTransform.scale.x;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::RIGHT);
		break;
	case CFade::UP:
		mTransform.pos = Vector3::zero - mTransform.scale.y;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::UP);
		break;
	case CFade::DOWN:
		mTransform.pos = Vector3::zero + mTransform.scale.y;
		doTween->DoMoveX(this, 0.5f, 5.0f, MOVEDIR::DOWN);
		break;
	default:
		break;
	}
}

CFade::CFade(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	doTween = new DoTween();
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
			//SetScene(newScene);
		}
	}
	if (fadeState != FadeState::NO_FADE)
	{
		doTween->Update();
	}
	CObject::Update();
}
