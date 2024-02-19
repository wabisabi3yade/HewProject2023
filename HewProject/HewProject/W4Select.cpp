#include "W4Select.h"

#define WORLDEX_OFFSETX (2.4f)	// EXの差分値(X軸)

W4Select::W4Select()
{
	stageNum = 4;	// ステージの数

	Vector2 uvOffset = { 1.0f / 3, 1.0f / 4 };
	worldNum->SetUV(uvOffset.x * 0, uvOffset.y * 2);

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

		// 配列に代入
		stgButton.push_back(btnWork);
		btnSelect->Regist(btnWork);

		// テクスチャ関連
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

	// 背景のテクスチャを設定
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
	
	// 数字をEXに変える
	worldNum->SetBuffer(oneBuf);
	worldNum->SetTexture(exTex);
	// 調整
	worldNum->mTransform.pos.x += 2.0f;
	worldNum->mTransform.scale.x *= 2.0f;

	// 最初の移動処理をするs
	BeginMove();
}

void W4Select::Update()
{

	if (isBeginFin)
	{
		// 入力
		Input();
	}
	// 最初の移動時に使用する処理はここ
	else
	{
		stageText->Update();

		// ステージテキストの背景の座標を更新
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

	// サンプルの移動処理
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

	// 前のステージ番号を更新
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