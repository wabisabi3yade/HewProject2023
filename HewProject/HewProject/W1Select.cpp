#include "W1Select.h"
#include "InputManager.h"

#define B_OFFSETX (1.4f)	// ボタンごとの差分（X座標）
#define B_OFFSETY (1.3f)	

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

	// ボタンの座標を設定
	int halfNum = (float)stageNum / 2;
	// ボタンの移動
	for (int i = 0; i < stgButton.size(); i++)
	{
		// 移動先の座標
		Vector3 p = firstBtnPos;
		p.x += (i % halfNum) * (B_OFFSETX * btnScale.x);
		p.y -= (i / halfNum) * (B_OFFSETY * btnScale.y);

		// 動かす
		stgButton[i]->GetDotween()->DoEaseOutBack(p, BEGIN_MOVETIME);
	}
}


// ボタンごとの差分（Y座標）
W1Select::W1Select()
{
	stageNum = 6;	// ステージの数

	firstBtnPos = { -6.5f, -1.0f, UI_POSZ };
	btnScale = { 1.4f, 1.3f, 1.0f };
	StgButton* btnWork = nullptr;

	Vector2 uvOffset = { 1.0f / 3, 1.0f / 4 };
	worldNum->SetUV(uvOffset.x * 1, uvOffset.y * 0);

	for (int i = 0; i < stageNum; i++)
	{
		// ボタン関連
		btnWork = new StgButton(stageBtnBuf, stageBtnTex, numberBuf, btnNumTex);
		btnWork->SetScale(btnScale);

		// ボタンの座標を設定
		Vector3 p = firstBtnPos;
		p.x -= BEGIN_MOVEMENT_X;
		// ボタンの座標を設定
		int halfNum = (float)stageNum / 2;
		p.x += (i % halfNum) * (B_OFFSETX * btnScale.x);
		p.y -= (i / halfNum) * (B_OFFSETY * btnScale.y);
		p.z -= i * UI_OFFSETZ;
		btnWork->SetPosition(p);

		btnWork->SetNum(i + 1);	// 数字をセット

		// 配列に代入
		stgButton.push_back(btnWork);
		btnSelect->Regist(btnWork);

		// テクスチャ関連
	}

	stgButton[c_pointStage - 1]->SetHighlight(true);

	stageTextPos.x = -6.5f;
	stageTextPos.y = 0.2f;
	stageText->mTransform.pos.y = 0.2f;

	stageText->mTransform.scale = stageText->mTransform.scale * 0.8f;
	stageText->mTransform.scale.z = 1.0f;
	stageTextBack->mTransform.scale = stageTextBack->mTransform.scale * 0.8f;
	stageTextBack->mTransform.scale.z = 1.0f;

	// 背景のテクスチャを設定
	D3D_LoadTexture(L"asset/Background/Stage1SelectBack.png", &backTex);
	backGround->SetTexture(backTex);

	// ワールド名に
	D3D_LoadTexture(L"asset/Text/World1Name.png", &worldNameTex);
	worldNameOffsetX = 1.0f;
	worldNamePos.y += 0.2f;
	worldName[1]->mTransform.pos.x += worldNameOffsetX;
	for (int i = 0; i < 2; i++)
	{
		// 文字をずらす
		worldName[i]->mTransform.pos.y = worldNamePos.y;
		worldName[i]->mTransform.pos.y -= i * WORLDNAME_OFFSETY;
		worldName[i]->SetTexture(worldNameTex);
	}

	// 最初の移動処理をする
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
