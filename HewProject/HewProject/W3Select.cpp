#include "W3Select.h"

W3Select::W3Select()
{
	stageNum = 4;	// �X�e�[�W�̐�

	Vector2 uvOffset = { 1.0f / 3, 1.0f / 4 };
	worldNum->SetUV(uvOffset.x * 0, uvOffset.y * 1);

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

		// �z��ɑ��
		stgButton.push_back(btnWork);
		btnSelect->Regist(btnWork);

		// �e�N�X�`���֘A
	}

	stgButton[c_pointStage - 1]->SetHighlight(true);

	// �w�i�̃e�N�X�`����ݒ�
	D3D_LoadTexture(L"asset/Background/Stage3SelectBack.png", &backTex);
	backGround->SetTexture(backTex);

	// �ŏ��̈ړ�����������s
	BeginMove();
}

void W3Select::Update()
{
	StageSelect::Update();
}

void W3Select::Draw()
{
	StageSelect::Draw();
}

W3Select::~W3Select()
{
	SAFE_RELEASE(backTex);

	for (auto a : stgButton)
	{
		CLASS_DELETE(a);
	}

	stgButton.clear();
	stgButton.shrink_to_fit();
}