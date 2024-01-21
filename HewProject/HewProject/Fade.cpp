#include "Fade.h"
#include "FadeUI.h"

#define FADE_BASE_POSZ (-0.5f)	// �t�F�[�h�̊���W
#define FADEOUT_POSX (2.0f)	// �t�F�[�h�A�E�g�̎��Ɍ�����X���W
#define FADE_SPEED (0.02f)	// �t�F�[�h�C���E�A�E�g���̑��x
#define LOAD_TIME (5.0f)	// ���[�h����

#define LOADING_BACKSPEED (0.001f)	// ���[�f�B���O���ɓ����w�i�̑��x 


Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	// ������
	isActive = false;
	state = STATE::STAY;

	// ��I�u�W�F�N�g
	// Dotween�g�p����
	fadeBase = new UI();
	fadeBase->MakeDotween();
	fadeBase->mTransform.pos.z = FADE_BASE_POSZ;

	// �w�i
	D3D_LoadTexture(L"asset/BackGround/fade2.png", &tex);
	D3D_CreateSquare({ 1,1 }, &vb);
	
	for (int i = 0; i < FADE_BACK_NUM; i++)
	{
		backGround[i] = new FadeUI(vb, tex);
		backGround[i]->mTransform.scale = { 3.0f, 2.0f, 1.0f };
		backGround[i]->SetActive(false);
	}
}

// �`��Ɏg�p����e�N�X�`��
Fade::~Fade()
{
	CLASS_DELETE(fadeBase);
	for (int i = 0; i < FADE_BACK_NUM; i++)
	{
		CLASS_DELETE(backGround[i]);
	}

	SAFE_RELEASE(tex);
	SAFE_RELEASE(vb);
}

Fade* Fade::GetInstance()
{
	// �쐬���Ă��Ȃ��Ȃ�
	if (instance == nullptr)
	{
		instance = new Fade();
	}

	return instance;
}

void Fade::Delete()
{
	CLASS_DELETE(instance);
}

void Fade::Update()
{
	if (!isActive) return;

	// ��Ԃ��Ƃɖ��t���[���s������
	switch (state)
	{
	case STATE::STAY:;
		break;

	case STATE::FADE_IN:
		FadeInUpdate();
		break;

	case STATE::LOADING:
		LoadingUpdate();
		break;

	case STATE::FADE_OUT:
		FadeOutUpdate();
		break;

	default:
		MessageBoxA(NULL, "Fade�N���XUpdate��state�̒l���͈͊O�ł�", "�G���[", MB_ICONERROR | MB_OK);
		break;
	}

	fadeBase->dotween->Update();

	// �t�F�[�h�S�̂̒��S���W��w�i�ɍX�V����
	for (int i = 0; i < FADE_BACK_NUM; i++)
	{
		backGround[i]->SetBasePos(fadeBase->mTransform.pos);
	}	
}

void Fade::FadeInUpdate()
{
	// �E�Ɉړ�����
	fadeBase->mTransform.pos.x += FADE_SPEED;

	// �^�񒆂ɂ�����
	if (fadeBase->mTransform.pos.x > 0.0f)
	{
		fadeBase->mTransform.pos.x = 0.0f;

		// ���̏�Ԃł�邱�Ƃ�����
		switch (nextState)
		{
		case STATE::FADE_OUT:
			FadeOutInit();
			break;

		case STATE::LOADING:
			LoadingInit();
			break;

		default:
			MessageBoxA(NULL, "Fade��FadeIn�֐��Ŏw�肵����Ԃ��͈͊O�ł�", "�G���[", MB_ICONERROR | MB_OK);
			break;
		}
	}
}

void Fade::LoadingInit()
{
	state = STATE::LOADING;
	loadingTime = 0.0f;

	//// 2���ڂ̉摜��\������
	//backGround[1]->SetActive(true);
	// ���W��1���ڂ̉摜�̍��ɂ���
	Vector3 v = { -backGround[1]->mTransform.scale.x , 0.0f, 0.0f };
	backGround[1]->SetOffset(v);


}

void Fade::LoadingUpdate()
{
	// �E���ɓ���
	float vecX = 1.0f;

	// �t�F�[�h�S�̂̒��S���W��w�i�ɍX�V����
	for (int i = 0; i < 1/*FADE_BACK_NUM*/; i++)
	{
		// �w�i���ړ�������
		float back_offset = backGround[i]->GetOffset().x;
		back_offset += vecX * LOADING_BACKSPEED;
		backGround[i]->SetOffset(back_offset);
	}


	// 1�t���[���̎���
	loadingTime += 1.0f / 60;
	// ���[�h���Ԃ���������
	if (loadingTime < LOAD_TIME) return;

	state = STATE::FADE_OUT;	// �t�F�[�h�A�E�g����
}

void Fade::FadeOutInit()
{
	// ��Ԃ��X�V����
	state = STATE::FADE_OUT;
}

void Fade::FadeOutUpdate()
{
	// �E�Ɉړ�����
	fadeBase->mTransform.pos.x += FADE_SPEED;

	// �w�i���ǂ�������ʊO�ɍs�����Ȃ�
	if (backGround[0]->mTransform.pos.x - backGround[0]->mTransform.scale.x / 2 > FADEOUT_POSX /*&&
		backGround[1]->mTransform.pos.x - backGround[1]->mTransform.scale.x / 2 > FADEOUT_POSX*/)
	{
		// ��\���ɂ���
		isActive = false;
		// �ҋ@��Ԃɂ���
		state = STATE::STAY;
		// �w�i���\���ɂ��Ă���
		for (int i = 0; i < FADE_BACK_NUM; i++)
		{
			// �I�t�Z�b�g��߂��Ă���
			backGround[i]->SetOffset(Vector3::zero);
			backGround[i]->SetActive(false);
		}
	}
}

void Fade::FadeIn(const STATE& _nextState)
{
	if (state != Fade::STATE::STAY) return;

	// �t�F�[�h�S�̂�\��
	isActive = true;

	// ���݁A���̂̏�Ԃ��X�V����
	state = STATE::FADE_IN;
	nextState = _nextState;

	// �w�i1���ڂ̏���������
	backGround[0]->SetActive(true);
	// �摜������ʒ[�ɍ����悤�ɃI�t�Z�b�g�𒲐�����
	Vector3 v = { (FADEOUT_POSX - backGround[0]->mTransform.scale.x) / 2, 0, 0};
	backGround[0]->SetOffset(v);

	// �ŏ��ɂ����ɒu��
	fadeBase->mTransform.pos = { -FADEOUT_POSX, 0.0f, 0.0f };
}

void Fade::Draw()
{
	if (!isActive) return;
	// �w�i�`��
	
	for (int i = 0; i < FADE_BACK_NUM; i++)
	{
		backGround[i]->Draw();
	}
	
}



