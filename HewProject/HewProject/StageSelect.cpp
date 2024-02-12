#include "StageSelect.h"
#include "ButtonSelect.h"
#include "InputManager.h"
#include "TextureFactory.h"
#include "ShadowUI.h"

#define BG_POSZ (1.1f)	// �w�i
#define SMPBACK_POSZ (1.0f)	

#define SMP_ROT (-10.0f)	// �T���v���̉�]�p�x 
#define SMPBACK_TARGET_POSX (3.5f)	// �T���v���w�i�ڕW�̒l
#define SMPBACK_BEGIN_OFFSETX (0.3f)	
#define SMP_MOVETIME (0.3f)	// �T���v���̈ړ�����

#define WOLRLDNUM_OFFSETX (2.0f)	// �����̍����l

void StageSelect::Input()
{
	btnSelect->FlagUpdate();

	InputManager* input = InputManager::GetInstance();
	if (input->GetMovement().x > 0.0f)
	{
		btnSelect->ButtonMove(1);
		c_pointStage++;
	}
	else if (input->GetMovement().x < 0.0f)
	{
		btnSelect->ButtonMove(-1);
		c_pointStage--;
	}

	// �I��ł���X�e�[�W�̐����擾
	c_pointStage = btnSelect->GetPointButton() + 1;
}

void StageSelect::SmpMove()
{
	// ���t���[���ŃX�e�[�W�ԍ����ς������
	if (c_pointStage != o_pointStage)
	{
		// doTween�̏�������
		stageSmpBack->dotween->Stop();
		// ��ʊO�ɔz�u
		stageSmpBack->mTransform.pos.x = SMPBACK_TARGET_POSX + SMPBACK_BEGIN_OFFSETX;
		stageSmpBack->SetAlpha(0.5f);

		stageSmpBack->dotween->DoMoveX(SMPBACK_TARGET_POSX, SMP_MOVETIME);
		stageSmpBack->dotween->Join(1.0f, SMP_MOVETIME, DoTweenUI::FUNC::ALPHA);
	}
}

StageSelect::StageSelect()
{
	// �{�^���w�i
	D3D_CreateSquare({ 2,1 }, &stageBtnBuf);
	D3D_LoadTexture(L"asset/UI/StageSelect_Btn.png", &stageBtnTex);
	// ����
	D3D_CreateSquare({ 3,4 }, &numberBuf);
	btnNumTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/Calorie_Number.png");
	D3D_LoadTexture(L"asset/UI/Number.png", &numberTex);

	btnSelect = new ButtonSelect();

	D3D_CreateSquare({ 1,1 }, &oneBuf);

	// �T���v���w�i
	stageSmpBackTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/White.png");
	stageSmpBack = new ShadowUI(oneBuf, stageSmpBackTex);
	stageSmpPos = { 3.5f, 0.0f, SMPBACK_POSZ };
	stageSmpBack->mTransform.pos = stageSmpPos;
	stageSmpBack->mTransform.pos.x += BEGIN_MOVEMENT_X;
	stageSmpBack->mTransform.scale = { 8.0f, 6.0f, 1.0f };
	stageSmpBack->mTransform.rotation.z = SMP_ROT;
	stageSmpBack->MakeDotween();

	// �w�i
	backGround = new UI(oneBuf, NULL);
	backGround->mTransform.pos.z = BG_POSZ;
	backGround->mTransform.scale = { SCREEN_RATIO_W, SCREEN_RATIO_H , 1.0f };

	// �X�^�[�gUI
	D3D_LoadTexture(L"asset/UI/B_Enter.png", &startTex);
	startUI = new ShadowUI(oneBuf, startTex);
	startUI->mTransform.pos = { -6.5f, -4.0f, 0.5f };
	startUI->mTransform.scale = { 2.4f, 0.8f, 1.0f };

	D3D_LoadTexture(L"asset/UI/T_Stage.png", &stageTex);
	stageText = new ShadowUI(oneBuf, stageTex);

	// �X�e�[�W�e�L�X�g
	stageTextPos = { -6.3f, -0.4f, UI_POSZ + UI_OFFSETZ };
	stageText->mTransform.pos = stageTextPos;
	stageText->mTransform.pos.x -= BEGIN_MOVEMENT_X;
	stageText->mTransform.scale = { 2.8f, 0.7f, 1.0f };
	stageText->MakeDotween();

	stageTextBack = new ShadowUI(oneBuf, TextureFactory::GetInstance()->Fetch(L"asset/UI/White.png"));
	stageTextBack->mTransform.pos = stageText->mTransform.pos;
	stageTextBack->mTransform.pos.z += UI_OFFSETZ;
	stageTextBack->mTransform.scale = { 4.0f,0.7f, 1.0f };
	stageTextBack->SetColor({ 245, 96, 149 });

	// World
	D3D_LoadTexture(L"asset/UI/T_World.png", &worldTextTex);
	worldText = new ShadowUI(oneBuf, worldTextTex);
	worldTextPos = { -6.0f, 4.0f, UI_POSZ };
	worldText->mTransform.pos = worldTextPos;
	worldText->mTransform.pos.x = worldTextPos.x - BEGIN_MOVEMENT_X;
	worldText->mTransform.scale = { 3.2f, 0.8f, 1.0f };
	worldText->MakeDotween();

	worldNum = new ShadowUI(numberBuf, numberTex);
	worldNum->mTransform.scale = { 0.7f, 0.7f, 1.0f };

	// �X�V
	o_pointStage = c_pointStage;
}

void StageSelect::Update()
{
	// �ŏ��̈ړ����Ɏg�p���鏈���͂���
	if (isBeginFin)
	{
		// ����
		Input();
	}
	else
	{
		stageText->Update();

		// �X�e�[�W�e�L�X�g�̔w�i�̍��W���X�V
		Vector3& pos = stageTextBack->mTransform.pos;
		pos = stageText->mTransform.pos;
		pos.z += UI_OFFSETZ;

		worldText->Update();
		worldNum->mTransform.pos = worldText->mTransform.pos;
		worldNum->mTransform.pos.x += WOLRLDNUM_OFFSETX;

	}

	// �T���v���̈ړ�����
	SmpMove();

	stageSmpBack->Update();








	for (auto a : stgButton)
	{
		a->Update();
	}

	// �O�̃X�e�[�W�ԍ����X�V
	o_pointStage = c_pointStage;
}

void StageSelect::LateUpdate()
{
}

void StageSelect::Draw()
{
	// �w�i�@���@�ʐ^�w�i�@���@�ʐ^�@���@�v���C���[�@���@UI

	backGround->Draw();

	stageSmpBack->Draw();

	worldText->Draw();
	worldNum->Draw();

	stageTextBack->Draw();
	stageText->Draw();

	for (auto a : stgButton)
	{
		a->Draw();
	}

	startUI->Draw();
}

StageSelect::~StageSelect()
{
	SAFE_RELEASE(stageBtnBuf);
	SAFE_RELEASE(stageBtnTex);

	SAFE_RELEASE(numberBuf);
	SAFE_RELEASE(numberTex);

	SAFE_RELEASE(oneBuf);
	CLASS_DELETE(stageSmpBack);
	CLASS_DELETE(backGround);
	CLASS_DELETE(btnSelect);

	SAFE_RELEASE(startTex);
	CLASS_DELETE(startUI);

	CLASS_DELETE(stageText);
	SAFE_RELEASE(stageTex);

	CLASS_DELETE(stageTextBack);

	CLASS_DELETE(worldText);
	SAFE_RELEASE(worldTextTex)

	CLASS_DELETE(worldNum);
}

void StageSelect::BeginMove()
{
	stageText->dotween->DoEaseOutBack(stageTextPos, BEGIN_MOVETIME);
	stageText->dotween->OnComplete([&]()
		{
			isBeginFin = true;
		});

	stageSmpBack->dotween->DoEaseOutBack(stageSmpPos, BEGIN_MOVETIME);

	worldText->dotween->DoEaseOutBack(worldTextPos, BEGIN_MOVETIME);

	// �{�^���̈ړ�
	for (int i = 0; i < stgButton.size(); i++)
	{
		// �ړ���̍��W
		Vector3 p = firstBtnPos;
		p.x += i * BTN_OFFSETX * btnScale.x;

		// ������
		stgButton[i]->GetDotween()->DoEaseOutBack(p, BEGIN_MOVETIME);
	}
}
