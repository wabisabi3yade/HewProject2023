#include "W1Select.h"


#define BTN_OFFSETX (1.3f)	// �{�^�����Ƃ̍����iX���W�j
#define BTN_OFFSETY (1.3f)	// �{�^�����Ƃ̍����iY���W�j
W1Select::W1Select()
{
	stageNum = 6;	// �X�e�[�W�̐�

	const Vector3 beginBtnPos = {-6.0f, 1.0f, 0.0f};
	const Vector3 btnScale = { 1.5f, 1.5f, 1.0f };

	StgButton* btnWork = nullptr;
	for (int i = 0; i < stageNum; i++)
	{
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
	}

	stgButton[0]->SetHighlight(true);
}

void W1Select::Update()
{
	StageSelect::Update();
}

void W1Select::Draw()
{
	for (auto a : stgButton)
	{
		a->Draw();
	}
}

W1Select::~W1Select()
{
	for (auto a : stgButton)
	{
		CLASS_DELETE(a);
	}

	stgButton.clear();
	stgButton.shrink_to_fit();
}
