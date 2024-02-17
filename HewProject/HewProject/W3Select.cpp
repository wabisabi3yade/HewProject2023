#include "W3Select.h"

W3Select::W3Select()
{
	stageNum = 4;	// ステージの数

	Vector2 uvOffset = { 1.0f / 3, 1.0f / 4 };
	worldNum->SetUV(uvOffset.x * 0, uvOffset.y * 1);

	StgButton* btnWork = nullptr;
	for (int i = 0; i < stageNum; i++)
	{
		// ボタン関連
		btnWork = new StgButton(stageBtnBuf, stageBtnTex, numberBuf, btnNumTex);
		btnWork->SetScale(btnScale);

		// ボタンの座標を設定
		Vector3 p = firstBtnPos;
		p.x += -BEGIN_MOVEMENT_X + i * (BTN_OFFSETX * btnScale.x);
		p.z -= i * UI_OFFSETZ;
		btnWork->SetPosition(p);

		btnWork->SetNum(i + 1);	// 数字をセット
		// ボタンシーン名設定

		switch (i)
		{
		case 0:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE3_1);
			break;

		case 1:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE3_2);
			break;

		case 2:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE3_3);
			break;

		case 3:
			btnWork->SetSceneName(CScene::SCENE_NAME::STAGE3_4);
			break;

		default:
			break;
		}

		// 配列に代入
		stgButton.push_back(btnWork);
		btnSelect->Regist(btnWork);


		// テクスチャ関連
	}

	stgButton[c_pointStage - 1]->SetHighlight(true);

	// 背景のテクスチャを設定
	D3D_LoadTexture(L"asset/Background/Stage3SelectBack.png", &backTex);
	backGround[0]->SetTexture(backTex);
	backGround[1]->SetTexture(backTex);
	backGround[2]->SetTexture(backTex);

	D3D_LoadTexture(L"asset/Text/World3Name.png", &worldNameTex);

	worldNameOffsetX = 2.5f;
	worldName[1]->mTransform.pos.x += worldNameOffsetX;
	for (int i = 0; i < 2; i++)
	{
		worldName[i]->SetTexture(worldNameTex);
	}

	// 最初の移動処理をするs
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