#include "W4Select.h"

#define WORLDEX_OFFSETX (2.4f)	// EX�̍����l(X��)

W4Select::W4Select()
{
	stageNum = 4;	// �X�e�[�W�̐�

	Vector2 uvOffset = { 1.0f / 3, 1.0f / 4 };
	worldNum->SetUV(uvOffset.x * 0, uvOffset.y * 2);

	StgButton* btnWork = nullptr;
	for (int i = 0; i < stageNum; i++)
	{
		// �{�^���֘A
		btnWork = new StgButton(stageBtnBuf, stageBtnTex, numberBuf, btnNumTex);
		btnWork->SetScale(btnScale);

		// �{�^���̍��W��ݒ�
		Vector3 p = firstBtnPos;
		p.x += -BEGIN_MOVEMENT_X + i * (BTN_OFFSETX * btnScale.x);
		p.z -= i * UI_OFFSETZ;
		btnWork->SetPosition(p);

		btnWork->SetNum(i + 1);	// �������Z�b�g

		// �{�^���V�[�����ݒ�
		switch (i)
		{
		case 0:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE4_1);
			break;

		case 1:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE4_2);
			break;

		case 2:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE4_3);
			break;

		case 3:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE4_4);
			break;

		default:
			break;
		}

		// �z��ɑ��
		stgButton.push_back(btnWork);
		btnSelect->Regist(btnWork);

		// �e�N�X�`���֘A
	}

	stgButton[c_pointStage - 1]->SetHighlight(true);

	stageSmpBack->SetColor({ 199, 178, 156 });

	D3DTEXTURE texWork;
	D3D_LoadTexture(L"asset/Sample/41.png", &texWork);
	stageSmpTex.push_back(texWork);

	D3D_LoadTexture(L"asset/Sample/42.png", &texWork);
	stageSmpTex.push_back(texWork);

	D3D_LoadTexture(L"asset/Sample/43.png", &texWork);
	stageSmpTex.push_back(texWork);

	D3D_LoadTexture(L"asset/Sample/44.png", &texWork);
	stageSmpTex.push_back(texWork);

	smp->SetTexture(stageSmpTex[0]);

	// �w�i�̃e�N�X�`����ݒ�
	D3D_LoadTexture(L"asset/Background/Stage4SelectBack.png", &backTex);
	backGround[0]->SetTexture(backTex);
	backGround[1]->SetTexture(backTex);
	backGround[2]->SetTexture(backTex);

	D3D_LoadTexture(L"asset/Text/World4Name.png", &worldNameTex);

	worldNameOffsetX = 1.0f;
	worldName[1]->mTransform.pos.x += worldNameOffsetX;
	for (int i = 0; i < 2; i++)
	{
		worldName[i]->SetTexture(worldNameTex);
	}

	D3D_LoadTexture(L"asset/Text/T_EX.png", &exTex);
	
	// ������EX�ɕς���
	worldNum->SetBuffer(oneBuf);
	worldNum->SetTexture(exTex);
	// ����
	worldNum->mTransform.pos.x += 2.0f;
	worldNum->mTransform.scale.x *= 2.0f;

	// �ŏ��̈ړ�����������s
	BeginMove();
}

void W4Select::Update()
{

	if (isBeginFin)
	{
		// ����
		Input();
	}
	// �ŏ��̈ړ����Ɏg�p���鏈���͂���
	else
	{
		stageText->Update();

		// �X�e�[�W�e�L�X�g�̔w�i�̍��W���X�V
		Vector3& pos = stageTextBack->mTransform.pos;
		pos = stageText->mTransform.pos;
		pos.z += UI_OFFSETZ;

		worldText->Update();
		worldNum->mTransform.pos = worldText->mTransform.pos;
		worldNum->mTransform.pos.x += WORLDEX_OFFSETX;

		for (int i = 0; i < 2; i++)
		{
			worldName[i]->Update();

		}

	}

	// �T���v���̈ړ�����
	SmpMove();

	stageSmpBack->Update();

	smp->mTransform.pos = stageSmpBack->mTransform.pos;
	smp->mTransform.pos.z -= UI_OFFSETZ;
	smp->SetAlpha(stageSmpBack->materialDiffuse.w);

	for (int i = 0; i < 3; i++)
	{
		backGround[i]->mTransform.pos.x -= 0.015f;
		if (backGround[i]->mTransform.pos.x < -24.0f)
		{
			backGround[i]->mTransform.pos.x = 22.0f;
		}

	}

	for (auto a : stgButton)
	{
		a->Update();
	}

	// �O�̃X�e�[�W�ԍ����X�V
	o_pointStage = c_pointStage;
}

void W4Select::Draw()
{
	StageSelect::Draw();
}

W4Select::~W4Select()
{
	SAFE_RELEASE(backTex);
	SAFE_RELEASE(exTex);

	for (auto a : stgButton)
	{
		CLASS_DELETE(a);
	}

	stgButton.clear();
	stgButton.shrink_to_fit();
}