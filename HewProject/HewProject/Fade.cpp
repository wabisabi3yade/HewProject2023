#include "Fade.h"
#include "FadeUI.h"

#define FADE_BASE_POSZ (-0.5f)	// �t�F�[�h�̊���W
#define FADEOUT_POSX (3.0f)	// �t�F�[�h�A�E�g�̎��Ɍ�����X���W
#define FADE_TIME (2.0f)
#define LOAD_TIME (5.0f)	// ���[�h����

#define LOADING_BACKSPEED (0.001f)	// ���[�f�B���O���ɓ����w�i�̑��x 


Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	// ������
	isActive = false;
	state = STATE::STAY;
	time = 0.0f;

	// ��I�u�W�F�N�g
	// Dotween�g�p����
	fadeBase = new UI();
	fadeBase->MakeDotween();
	fadeBase->mTransform.pos.z = FADE_BASE_POSZ;

	// �w�i
	D3D_LoadTexture(L"asset/BackGround/fade2.png", &tex);
	D3D_CreateSquare({ 1,1 }, &vb);

	backGround = new FadeUI(vb, tex);
	backGround->mTransform.scale = { 3.0f, 2.0f, 1.0f };
	backGround->SetActive(false);

}

// �`��Ɏg�p����e�N�X�`��
Fade::~Fade()
{
	CLASS_DELETE(fadeBase);

	CLASS_DELETE(backGround);

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
}

void Fade::FadeInUpdate()
{
	time += 1.0f / 60;

	// �E�Ɉړ�����(�C�[�W���O)
	backGround->mTransform.pos.x  = startPos + distance * (1 - std::pow(1 - time / FADE_TIME, 3));

	// �^�񒆂ɂ�����
	if (time > FADE_TIME)
	{
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
	time = 0.0f;
}

void Fade::LoadingUpdate()
{
	// �E���ɓ���
	float vecX = 1.0f;

	// �w�i���ړ�������
	backGround->mTransform.pos.x += vecX * LOADING_BACKSPEED;

	// 1�t���[���̎���
	time += 1.0f / 60;
	// ���[�h���Ԃ���������
	if (time < LOAD_TIME) return;

	state = STATE::FADE_OUT;	// �t�F�[�h�A�E�g����

	FadeOutInit();
}

void Fade::FadeOutInit()
{
	// ��Ԃ��X�V����
	state = STATE::FADE_OUT;

	//�����𑪂�
	startPos = backGround->mTransform.pos.x;
	distance = FADEOUT_POSX - startPos;

	time = 0.0f;
}

void Fade::FadeOutUpdate()
{
	time += 1.0f / 60;

	// �E�Ɉړ�����
	backGround->mTransform.pos.x  = startPos + distance * (1 - std::pow(1 - time / FADE_TIME, 3));

	// �w�i����ʊO�ɍs�����Ȃ�
	if (time > FADE_TIME)
	{
		// ��\���ɂ���
		isActive = false;
		// �w�i���\���ɂ���
		backGround->SetActive(false);
		// �ҋ@��Ԃɂ���
		state = STATE::STAY;
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

	// ��ʍ��[�ɔz�u����
	backGround->mTransform.pos.x = -FADEOUT_POSX;

	//�����𑪂�
	startPos = backGround->mTransform.pos.x;
	distance = 0.0f - startPos;

	time = 0.0f;

	// �w�i�̏���������
	backGround->SetActive(true);
}

void Fade::Draw()
{
	if (!isActive) return;
	
	// �w�i�`��
	backGround->Draw();
}



