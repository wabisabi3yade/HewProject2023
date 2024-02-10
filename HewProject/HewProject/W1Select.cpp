#include "W1Select.h"


#define BTN_OFFSETX (1.3f)	// ボタンごとの差分（X座標）
#define BTN_OFFSETY (1.3f)	// ボタンごとの差分（Y座標）
W1Select::W1Select()
{
	stageNum = 6;	// ステージの数

	const Vector3 beginBtnPos = {-6.0f, 1.0f, 0.0f};
	const Vector3 btnScale = { 1.5f, 1.5f, 1.0f };

	StgButton* btnWork = nullptr;
	for (int i = 0; i < stageNum; i++)
	{
		btnWork = new StgButton(stageBtnBuf, stageBtnTex, numberBuf, numberTex);
		btnWork->SetScale(btnScale);

		// ボタンの座標を設定
		Vector3 p = beginBtnPos;
		int halfNum = (float)stageNum / 2;
		p.x += (i % halfNum) * (BTN_OFFSETX * btnScale.x);
		p.y -= (i / halfNum) * (BTN_OFFSETY * btnScale.y);
		p.z -= i * UI_OFFSETZ;
		btnWork->SetPosition(p);

		btnWork->SetNum(i + 1);	// 数字をセット

		// 配列に代入
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
