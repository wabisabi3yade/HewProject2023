#include "W1Select.h"
#include "InputManager.h"

#define BTN_OFFSETX (1.3f)	// ボタンごとの差分（X座標）
#define BTN_OFFSETY (1.3f)	

#define UP_BTN_MOVEMENT (3)	// 上入力で移動するボタンの数

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

	// 選んでいるステージの数を取得
	c_pointStage = btnSelect->GetPointButton() + 1;
}


// ボタンごとの差分（Y座標）
W1Select::W1Select()
{
	stageNum = 6;	// ステージの数

	const Vector3 beginBtnPos = { -6.0f, 1.0f, UI_POSZ };
	const Vector3 btnScale = { 1.5f, 1.5f, 1.0f };

	StgButton* btnWork = nullptr;
	for (int i = 0; i < stageNum; i++)
	{
		// ボタン関連
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

		// テクスチャ関連
	}

	stgButton[c_pointStage - 1]->SetHighlight(true);

	// 背景のテクスチャを設定
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
