#include "W1Select.h"
#include "InputManager.h"
#include "CSceneManager.h"

#define B_OFFSETX (1.4f)	// �{�^�����Ƃ̍����iX���W�j
#define B_OFFSETY (1.3f)	

#define UP_BTN_MOVEMENT (3)	// ����͂ňړ�����{�^���̐�

void W1Select::Input()
{
	if (isSceneMoving) return;
	btnSelect->FlagUpdate();

	InputManager* input = InputManager::GetInstance();
	if (input->GetMovement().x > 0.0f)
	{
		btnSelect->ButtonMove(1);
	}
	else if (input->GetMovement().x < 0.0f)
	{
		btnSelect->ButtonMove(-1);
	}
	else if (input->GetMovement().y > 0.0f)
	{
		btnSelect->ButtonMove(UP_BTN_MOVEMENT);
	}
	else if (input->GetMovement().y < 0.0f)
	{
		btnSelect->ButtonMove(-UP_BTN_MOVEMENT);
	}

	// �I��ł���X�e�[�W�̐����擾
	c_pointStage = btnSelect->GetPointButton() + 1;

	// �ړ������̂�
	if (c_pointStage != o_pointStage)
	{
		/*XA_Play(SOUND_LABEL::S_MOVEBUTTON);*/
	}

	if (input->GetInputTrigger(InputType::DECIDE))
	{
		// �擾
		CScene::SCENE_NAME next = static_cast<CScene::SCENE_NAME>(btnSelect->GetPointSceneName());

		if (Fade::GetInstance()->GetState() != Fade::STATE::STAY) return;

		XA_Play(SOUND_LABEL::S_PUSH_STAGEBTN);

		Fade::GetInstance()->FadeIn(Fade::STATE::LOADING, nullptr, next);

		isSceneMoving = true;
	}

	if (input->GetInputTrigger(InputType::CANCEL))
	{
		if (Fade::GetInstance()->GetState() != Fade::STATE::STAY) return;
		Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, nullptr, CScene::SCENE_NAME::STAGE1);
		isSceneMoving = true;
	}
}

void W1Select::BeginMove()
{
	stageText->dotween->DoEaseOutBack(stageTextPos, BEGIN_MOVETIME);
	stageText->dotween->OnComplete([&]()
		{
			isBeginFin = true;
		});

	stageSmpBack->dotween->DoEaseOutBack(stageSmpPos, BEGIN_MOVETIME);

	worldText->dotween->DoEaseOutBack(worldTextPos, BEGIN_MOVETIME);
	worldNameOffsetX = 1.0f;
	for (int i = 0; i < 2; i++)
	{
		Vector3 v = worldNamePos;
		v.x += i * worldNameOffsetX;
		v.y -= i * WORLDNAME_OFFSETY;
		v.z -= i * UI_OFFSETZ;
		worldName[i]->dotween->DoEaseOutBack(v, BEGIN_MOVETIME);
	}

	// �{�^���̍��W��ݒ�
	int halfNum = (float)stageNum / 2;
	// �{�^���̈ړ�
	for (int i = 0; i < stgButton.size(); i++)
	{
		// �ړ���̍��W
		Vector3 p = firstBtnPos;
		p.x += (i % halfNum) * (B_OFFSETX * btnScale.x);
		p.y -= (i / halfNum) * (B_OFFSETY * btnScale.y);

		// ������
		stgButton[i]->GetDotween()->DoEaseOutBack(p, BEGIN_MOVETIME);
	}
}


// �{�^�����Ƃ̍����iY���W�j
W1Select::W1Select()
{
	stageNum = 6;	// �X�e�[�W�̐�

	firstBtnPos = { -6.5f, -1.0f, UI_POSZ };
	btnScale = { 1.4f, 1.3f, 1.0f };
	StgButton* btnWork = nullptr;

	Vector2 uvOffset = { 1.0f / 3, 1.0f / 4 };
	worldNum->SetUV(uvOffset.x * 1, uvOffset.y * 0);

	for (int i = 0; i < stageNum; i++)
	{
		// �{�^���֘A
		btnWork = new StgButton(stageBtnBuf, stageBtnTex, numberBuf, btnNumTex);
		btnWork->SetScale(btnScale);

		// �{�^���̍��W��ݒ�
		Vector3 p = firstBtnPos;
		p.x -= BEGIN_MOVEMENT_X;
		// �{�^���̍��W��ݒ�
		int halfNum = (float)stageNum / 2;
		p.x += (i % halfNum) * (B_OFFSETX * btnScale.x);
		p.y -= (i / halfNum) * (B_OFFSETY * btnScale.y);
		p.z -= i * UI_OFFSETZ;
		btnWork->SetPosition(p);

		btnWork->SetNum(i + 1);	// �������Z�b�g

		// �{�^���V�[�����ݒ�
		switch (i)
		{
		case 0:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE1_1);
			break;

		case 1:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE1_2);
			break;

		case 2:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE1_3);
			break;

		case 3:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE1_4);
			break;

		case 4:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE1_5);
			break;

		case 5:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE1_6);
			break;

		default:
			break;
		}

		// �z��ɑ��
		stgButton.push_back(btnWork);
		btnSelect->Regist(btnWork);


	}
	D3DTEXTURE texWork;
	D3D_LoadTexture(L"asset/Sample/11.png", &texWork);

	stageSmpTex.push_back(texWork);

	smp->SetTexture(stageSmpTex[0]);

	stgButton[c_pointStage - 1]->SetHighlight(true);

	stageTextPos.x = -6.5f;
	stageTextPos.y = 0.2f;
	stageText->mTransform.pos.y = 0.2f;

	stageText->mTransform.scale = stageText->mTransform.scale * 0.8f;
	stageText->mTransform.scale.z = 1.0f;
	stageTextBack->mTransform.scale = stageTextBack->mTransform.scale * 0.8f;
	stageTextBack->mTransform.scale.z = 1.0f;

	// �w�i�̃e�N�X�`����ݒ�
	D3D_LoadTexture(L"asset/Background/Stage1SelectBack.png", &backTex);
	backGround[0]->SetTexture(backTex);
	backGround[1]->SetTexture(backTex);
	backGround[2]->SetTexture(backTex);

	// ���[���h����
	D3D_LoadTexture(L"asset/Text/World1Name.png", &worldNameTex);
	worldNameOffsetX = 1.0f;
	worldNamePos.y += 0.2f;
	worldName[1]->mTransform.pos.x += worldNameOffsetX;
	for (int i = 0; i < 2; i++)
	{
		// ���������炷
		worldName[i]->mTransform.pos.y = worldNamePos.y;
		worldName[i]->mTransform.pos.y -= i * WORLDNAME_OFFSETY;
		worldName[i]->SetTexture(worldNameTex);
	}

	// �ŏ��̈ړ�����������
	BeginMove();
}

void W1Select::Update()
{
	StageSelect::Update();
}

void W1Select::Draw()
{
	StageSelect::Draw();
}

W1Select::~W1Select()
{
	SAFE_RELEASE(backTex);
	SAFE_RELEASE(worldNameTex);

	for (auto a : stgButton)
	{
		CLASS_DELETE(a);
	}

	stgButton.clear();
	stgButton.shrink_to_fit();
}
