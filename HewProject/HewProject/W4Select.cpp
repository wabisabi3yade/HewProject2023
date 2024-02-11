#include "W4Select.h"

W4Select::W4Select()
{
	stageNum = 4;	// ステージの数

	const Vector3 beginBtnPos = { -7.0f, 0.0f, UI_POSZ };

	StgButton* btnWork = nullptr;
	for (int i = 0; i < stageNum; i++)
	{
		// ボタン関連
		btnWork = new StgButton(stageBtnBuf, stageBtnTex, numberBuf, numberTex);
		btnWork->SetScale(btnScale);

		// ボタンの座標を設定
		Vector3 p = firstBtnPos;
		p.x += -BEGIN_MOVEMENT_X + i * (BTN_OFFSETX * btnScale.x);
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
	D3D_LoadTexture(L"asset/Background/Stage2SelectBack.png", &backTex);
	backGround->SetTexture(backTex);
}

void W4Select::Update()
{
	StageSelect::Update();
}

void W4Select::Draw()
{
	StageSelect::Draw();
}

W4Select::~W4Select()
{
	SAFE_RELEASE(backTex);

	for (auto a : stgButton)
	{
		CLASS_DELETE(a);
	}

	stgButton.clear();
	stgButton.shrink_to_fit();
}