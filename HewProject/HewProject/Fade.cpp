#include "Fade.h"
#include "FadeUI.h"
#include "NowLoadingText.h"
#include "TextureFactory.h"
#include "CScene.h"



#define FADESCALE_X (20.0f)
#define FADESCALE_Y (9.0f)
#define FADE_BASE_POSZ (-0.45f)	// �t�F�[�h�̊���W
#define FADEOUT_POSX (16.0f + FADESCALE_X / 2.0f)	// �t�F�[�h�A�E�g�̎��Ɍ�����X���W

#define FADE_TIME (1.5f)
#define LOAD_TIME (2.5f)	// ���[�h����

#define LOADING_BACKSPEED (0.007f)	// ���[�f�B���O���ɓ����w�i�̑��x 
#define NOWLOADING_OFFSET_Z (0.1f)	// NowLoading�̃e�L�X�g���w�i����̍� 

Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	// ������
	isActive = false;
	state = STATE::STAY;
	loadingTime = 0.0f;

	// ��I�u�W�F�N�g
	// Dotween�g�p����
	fadeBase = new UI();
	fadeBase->MakeDotween();
	fadeBase->mTransform.pos.z = FADE_BASE_POSZ;

	// �w�i
	tex = TextureFactory::GetInstance()->Fetch(L"asset/UI/fade_BackBlue.png");
	D3D_CreateSquare({ 1,1 }, &vb);

	backGround = new FadeUI(vb, tex);
	backGround->MakeDotween();
	backGround->mTransform.scale = {FADESCALE_X, FADESCALE_Y, 1.0f };
	backGround->SetActive(false);
	backGround->mTransform.pos.z = FADE_BASE_POSZ;
}

// �`��Ɏg�p����e�N�X�`��
Fade::~Fade()
{
	CLASS_DELETE(fadeBase);

	CLASS_DELETE(backGround);

	CLASS_DELETE(nowLoading);

	SAFE_RELEASE(vb);
}

void Fade::SceneChange(int _set)
{
	isSceneChange = true;

	nextScene = _set;
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

	backGround->dotween->Update();

	if (nowLoading != nullptr)
	{
		nowLoading->Update();
	}
}

void Fade::FadeInUpdate()
{
}

void Fade::LoadingInit()
{
	//�V�[�������[�h�V�[���ɍs��
	ChangeLoadScene();

	state = STATE::LOADING;
	loadingTime = 0.0f;


	// �e�L�X�g���쐬����
	nowLoading = new NowLoadingText();
}

void Fade::ChangeLoadScene()
{
	isSceneChange = true;
}

void Fade::LoadingUpdate()
{
	// �E���ɓ���
	float vecX = 1.0f;

	// �w�i���ړ�������
	backGround->mTransform.pos.x += vecX * LOADING_BACKSPEED;

	// 1�t���[���̎���
	loadingTime += 1.0f / 60;
	// ���[�h���Ԃ���������
	if (loadingTime < LOAD_TIME) return;

	// �e�L�X�g���������
	CLASS_DELETE(nowLoading);

	state = STATE::FADE_OUT;	// �t�F�[�h�A�E�g����

	FadeOutInit();
}

void Fade::FadeOutInit()
{
	// ��Ԃ��X�V����
	state = STATE::FADE_OUT;

	// �����ő�������֐������s����
	func();

	// �V�[����ς���Ƃ��ɌĂԊ֐�
	


	Vector3 v = Vector3::zero;
	v.x = FADEOUT_POSX;
	v.z = FADE_BASE_POSZ;
	backGround->dotween->DoEaseOutCubic(v, FADE_TIME);
	backGround->dotween->OnComplete([&]()
		{
			// ��\���ɂ���
			isActive = false;
			// �w�i���\���ɂ���
			backGround->SetActive(false);
			// �ҋ@��Ԃɂ���
			state = STATE::STAY;
		});
}

void Fade::FadeOutUpdate()
{
}

void Fade::FadeIn(const STATE& _nextState, std::function<void()> _onFunc, int _setScene)
{
	if (state != Fade::STATE::STAY) return;

	// �����_����������
	func = _onFunc;

	ChangeLoadScene();


	// �t�F�[�h�S�̂�\��
	isActive = true;

	// ���݁A���̂̏�Ԃ��X�V����
	state = STATE::FADE_IN;
	nextState = _nextState;

	// ��ʍ��[�ɔz�u����
	backGround->mTransform.pos.x = -FADEOUT_POSX;

	// �w�i�̏���������
	backGround->SetActive(true);

	// �t�F�[�h����ʒ[�ɓ��B����u�Ԃ̍��W
	Vector3 v = Vector3::zero;
	v.z = FADE_BASE_POSZ;
	backGround->dotween->DoEaseOutCubic(v, FADE_TIME);
	backGround->dotween->OnComplete([&]()
		{
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
		});
}

void Fade::Draw()
{
	if (!isActive) return;

	// �w�i�`��
	backGround->Draw();

	if (nowLoading != nullptr)
	{
		nowLoading->Draw();
	}
}

bool Fade::GetIsChange()
{
	return false;
}

bool Fade::GetLoadChange()
{
	if (isSceneChange)
	{
		isSceneChange = false;
		return true;
	}

	return false;
}


