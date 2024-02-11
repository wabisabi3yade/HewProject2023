#include "W1Select.h"
#include "InputManager.h"

#define BTN_OFFSETX (1.3f)	// �{�^�����Ƃ̍����iX���W�j
#define BTN_OFFSETY (1.3f)	

#define UP_BTN_MOVEMENT (3)	// ����͂ňړ�����{�^���̐�

void W1Select::Input()
{
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
}


// �{�^�����Ƃ̍����iY���W�j
W1Select::W1Select()
{
	stageNum = 6;	// �X�e�[�W�̐�

	const Vector3 beginBtnPos = { -6.0f, 1.0f, UI_POSZ };
	const Vector3 btnScale = { 1.5f, 1.5f, 1.0f };

	StgButton* btnWork = nullptr;
	for (int i = 0; i < stageNum; i++)
	{
		// �{�^���֘A
		btnWork = new StgButton(stageBtnBuf, stageBtnTex, numberBuf, numberTex);
		btnWork->SetScale(btnScale);

		// �{�^���̍��W��ݒ�
		Vector3 p = beginBtnPos;
		int halfNum = (float)stageNum / 2;
		p.x += (i % halfNum) * (BTN_OFFSETX * btnScale.x);
		p.y -= (i / halfNum) * (BTN_OFFSETY * btnScale.y);
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
	D3D_LoadTexture(L"asset/Background/Stage1SelectBack.png", &backTex);
	backGround->SetTexture(backTex);
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

	for (auto a : stgButton)
	{
		CLASS_DELETE(a);
	}

	stgButton.clear();
	stgButton.shrink_to_fit();
}
