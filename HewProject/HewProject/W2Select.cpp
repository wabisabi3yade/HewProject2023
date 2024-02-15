#include "W2Select.h"

W2Select::W2Select()
{
	stageNum = 4;	// �X�e�[�W�̐�

	Vector2 uvOffset = { 1.0f / 3, 1.0f / 4 };
	worldNum->SetUV(uvOffset.x * 2, uvOffset.y * 0);

	StgButton* btnWork = nullptr;
	for (int i = 0; i < stageNum; i++)
	{
		// �{�^���֘A
		btnWork = new StgButton(stageBtnBuf, stageBtnTex, numberBuf, btnNumTex);
		btnWork->SetScale(btnScale);

		// �{�^���̍��W��ݒ�
		Vector3 p = firstBtnPos;
		p.x +=  - BEGIN_MOVEMENT_X + i * (BTN_OFFSETX * btnScale.x);
		p.z -= i * UI_OFFSETZ;
		btnWork->SetPosition(p);

		btnWork->SetNum(i + 1);	// �������Z�b�g

		// �{�^���V�[�����ݒ�
		switch (i)
		{
		case 0:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE2_1);
			break;

		case 1:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE2_2);
			break;

		case 2:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE2_3);
			break;

		case 3:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE2_4);
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

	// �w�i�̃e�N�X�`����ݒ�
	D3D_LoadTexture(L"asset/Background/Stage2SelectBack.png", &backTex);
	backGround->SetTexture(backTex);

	D3D_LoadTexture(L"asset/Text/World2Name.png", &worldNameTex);

	worldNameOffsetX = 3.0f;
	worldName[1]->mTransform.pos.x += worldNameOffsetX;
	for (int i = 0; i < 2; i++)
	{
		worldName[i]->SetTexture(worldNameTex);
	}

	// �ŏ��̈ړ�����������s
	BeginMove();
}

void W2Select::Update()
{
	StageSelect::Update();
}

void W2Select::Draw()
{
	StageSelect::Draw();
}

W2Select::~W2Select()
{
	SAFE_RELEASE(backTex);

	for (auto a : stgButton)
	{
		CLASS_DELETE(a);
	}

	stgButton.clear();
	stgButton.shrink_to_fit();
}
