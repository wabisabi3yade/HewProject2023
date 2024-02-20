#include "Fade.h"
#include "FadeUI.h"
#include "NowLoadingText.h"
#include "TextureFactory.h"
#include "CScene.h"
#include"xa2.h"
#include "Vector2.h"
#include "StageMoveText.h"

#define FADESCALE_X (20.0f)
#define FADESCALE_Y (9.0f)
#define FADE_BASE_POSZ (-0.498f)	// �t�F�[�h�̊���W
#define FADEOUT_POSX (16.0f + FADESCALE_X / 2.0f)	// �t�F�[�h�A�E�g�̎��Ɍ�����X���W

#define FADE_TIME (1.5f)
#define LOAD_TIME (2.0f)	// ���[�h����

#define LOADING_BACKSPEED (0.007f)	// ���[�f�B���O���ɓ����w�i�̑��x 
#define NOWLOADING_OFFSET_Z (0.1f)	// NowLoading�̃e�L�X�g���w�i����̍� 

#define FADEIN_DELAYTIME (0.5f)	// �t�F�[�h�C���Ă΂�ăt�F�[�h�C������܂łɑҋ@����

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
	backGround->mTransform.scale = { FADESCALE_X, FADESCALE_Y, 1.0f };
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

	CLASS_DELETE(moveText);
}

void Fade::SceneChange()
{
	isSceneChange = true;
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

	backGround->dotween->Update();

	// ��Ԃ��Ƃɖ��t���[���s������
	switch (state)
	{
	case STATE::STAY:
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

	case STATE::MOVING:
		MovingUpdate();
		break;


	default:
		MessageBoxA(NULL, "Fade�N���XUpdate��state�̒l���͈͊O�ł�", "�G���[", MB_ICONERROR | MB_OK);
		break;
	}

	if (isFadeInEnd)
	{
		isFadeInEnd = false;

		FadeOutInit();
	}


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
	isLoadChange = true;
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
	if (func != nullptr)
	{
		func();
	}
	// �V�[����ς���Ƃ��ɌĂԊ֐�
	if (nextScene != CScene::SCENE_NAME::NONE)
		SceneChange();

	Vector3 v = Vector3::zero;
	v.x = FADEOUT_POSX;
	v.z = FADE_BASE_POSZ;

	backGround->dotween->Stop();
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

	// ���̃V�[����������
	nextScene = _setScene;


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

	backGround->dotween->DelayedCall(FADEIN_DELAYTIME, [&]
		{
			XA_Play(SOUND_LABEL::S_FADE_IN);
		});
	backGround->dotween->DoDelay(FADEIN_DELAYTIME);
	backGround->dotween->Append(v, FADE_TIME, DoTweenUI::FUNC::EASE_OUTCUBIC);
	backGround->dotween->OnComplete([&]()
		{
			switch (nextState)
			{
			case STATE::FADE_OUT:
				/*FadeOutInit();*/ isFadeInEnd = true;
				break;

			case STATE::LOADING:
				LoadingInit();
				break;

			case STATE::MOVING:
				MovingInit();
				break;

			default:
				MessageBoxA(NULL, "Fade��FadeIn�֐��Ŏw�肵����Ԃ��͈͊O�ł�", "�G���[", MB_ICONERROR | MB_OK);
				break;
			}
		});
}

void Fade::MovingInit()
{
	//�V�[�������[�h�V�[���ɍs��
	ChangeLoadScene();

	state = STATE::MOVING;
	loadingTime = 0.0f;

	// ���̃X�e�[�W�̐������߂�
	INT_XY nextStageNum = JudgeNum();

	moveText = new StageMoveText(nextStageNum.x, nextStageNum.y);
}

void Fade::MovingUpdate()
{
	// �E���ɓ���
	float vecX = 1.0f;

	// �w�i���ړ�������
	backGround->mTransform.pos.x += vecX * LOADING_BACKSPEED;

	if (moveText != nullptr)
		moveText->Update();

	// 1�t���[���̎���
	loadingTime += 1.0f / 60;
	// ���[�h���Ԃ���������
	if (loadingTime < LOAD_TIME) return;

	// �e�L�X�g���������
	CLASS_DELETE(moveText);

	state = STATE::FADE_OUT;	// �t�F�[�h�A�E�g����

	FadeOutInit();
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

	if (moveText != nullptr)
	{
		moveText->Draw();
	}
}


Fade::INT_XY Fade::JudgeNum()
{
	INT_XY w_sNum = {};
	switch (nextScene)
	{
	case CScene::STAGE1_1:
	case CScene::STAGE1_2:
	case CScene::STAGE1_3:
	case CScene::STAGE1_4:
	case CScene::STAGE1_5:
	case CScene::STAGE1_6:
		w_sNum.x = 1;
		break;

	case CScene::STAGE2_1:
	case CScene::STAGE2_2:
	case CScene::STAGE2_3:
	case CScene::STAGE2_4:
		w_sNum.x = 2;
		break;

	case CScene::STAGE3_1:
	case CScene::STAGE3_2:
	case CScene::STAGE3_3:
	case CScene::STAGE3_4:
		w_sNum.x = 3;
		break;

	case CScene::STAGE4_1:
	case CScene::STAGE4_2:
	case CScene::STAGE4_3:
	case CScene::STAGE4_4:
		w_sNum.x = 4;
		break;

	default:
		break;
	}

	switch (nextScene)
	{
	case CScene::STAGE1_1:
	case CScene::STAGE2_1:
	case CScene::STAGE3_1:
	case CScene::STAGE4_1:
		w_sNum.y = 1;
		break;

	case CScene::STAGE1_2:
	case CScene::STAGE2_2:
	case CScene::STAGE3_2:
	case CScene::STAGE4_2:
		w_sNum.y = 2;
		break;

	case CScene::STAGE1_3:
	case CScene::STAGE2_3:
	case CScene::STAGE3_3:
	case CScene::STAGE4_3:
		w_sNum.y = 3;
		break;


	case CScene::STAGE1_4:
	case CScene::STAGE2_4:
	case CScene::STAGE3_4:
	case CScene::STAGE4_4:
		w_sNum.y = 4;
		break;


	case CScene::STAGE1_5:
		w_sNum.y = 5;
		break;
	case CScene::STAGE1_6:
		w_sNum.y = 6;
		break;

	default:
		break;
	}

	return w_sNum;
}

bool Fade::GetIsChange()
{
	if (isSceneChange)
	{
		isSceneChange = false;
		return true;
	}

	return false;
}

bool Fade::GetLoadChange()
{
	if (isLoadChange)
	{
		isLoadChange = false;
		return true;
	}

	return false;
}

int Fade::GetNextScene()
{
	return nextScene;
}


