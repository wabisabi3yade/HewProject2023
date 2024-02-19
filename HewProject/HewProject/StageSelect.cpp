#include "StageSelect.h"
#include "ButtonSelect.h"
#include "InputManager.h"
#include "TextureFactory.h"
#include "ShadowUI.h"
#include "CSceneManager.h"

#define BG_POSZ (1.1f)	// 背景
#define SMPBACK_POSZ (1.0f)	

#define SMP_ROT (-7.50f)	// サンプルの回転角度 
#define SMPBACK_TARGET_POSX (3.5f)	// サンプル背景目標の値
#define SMPBACK_BEGIN_OFFSETX (0.3f)	
#define SMP_MOVETIME (0.3f)	// サンプルの移動時間

#define WOLRLDNUM_OFFSETX (2.0f)	// 数字の差分値

#define WORLDNUM_SHADOWOFFSETX (0.03f)
#define WORLDNUM_SHADOWOFFSETY (0.03f)

#define SIN_POWER (0.1f)
#define SIN_SPEED (1.0f)

void StageSelect::Input()
{

	if (isSceneMoving) return;

	btnSelect->FlagUpdate();

	InputManager* input = InputManager::GetInstance();
	if (input->GetMovement().x > 0.0f)
	{
		btnSelect->ButtonMove(1);
		c_pointStage++;
	}
	else if (input->GetMovement().x < 0.0f)
	{
		btnSelect->ButtonMove(-1);
		c_pointStage--;
	}
	// 選んでいるステージの数を取得
	c_pointStage = btnSelect->GetPointButton() + 1;

	// サンプルの画像変える
	smp->SetTexture(stageSmpTex[c_pointStage - 1]);

	// 移動したので
	if (c_pointStage != o_pointStage)
	{
		/*XA_Play(SOUND_LABEL::S_MOVEBUTTON);*/
	}

	if (input->GetInputTrigger(InputType::DECIDE))
	{
		if (Fade::GetInstance()->GetState() != Fade::STATE::STAY) return;

		XA_Play(SOUND_LABEL::S_PUSH_STAGEBTN);

		// 取得
		CScene::SCENE_NAME next = static_cast<CScene::SCENE_NAME>(btnSelect->GetPointSceneName());

			Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, nullptr, next);
			isSceneMoving = true;


	}
	else if (input->GetInputTrigger(InputType::CANCEL))
	{
		if (Fade::GetInstance()->GetState() == Fade::STATE::STAY)
		{
			Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, nullptr, CScene::SCENE_NAME::STAGE1);
			isSceneMoving = true;
		}

	}


}

void StageSelect::SmpMove()
{
	// 今フレームでステージ番号が変わったら
	if (c_pointStage != o_pointStage)
	{
		// doTweenの処理消去
		stageSmpBack->dotween->Stop();
		// 画面外に配置
		stageSmpBack->mTransform.pos.x = SMPBACK_TARGET_POSX + SMPBACK_BEGIN_OFFSETX;
		stageSmpBack->SetAlpha(0.5f);

		stageSmpBack->dotween->DoMoveX(SMPBACK_TARGET_POSX, SMP_MOVETIME);
		stageSmpBack->dotween->Join(1.0f, SMP_MOVETIME, DoTweenUI::FUNC::ALPHA);

	}
	else
	{
		/*stageSmpBack*/
	}
}

StageSelect::StageSelect()
{
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_STAGESELECT);

	// ボタン背景
	D3D_CreateSquare({ 2,1 }, &stageBtnBuf);
	D3D_LoadTexture(L"asset/UI/StageSelect_Btn.png", &stageBtnTex);
	// 数字
	D3D_CreateSquare({ 3,4 }, &numberBuf);
	btnNumTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/Calorie_Number.png");
	D3D_LoadTexture(L"asset/UI/Number.png", &numberTex);

	btnSelect = new ButtonSelect();

	D3D_CreateSquare({ 1,1 }, &oneBuf);

	// サンプル背景
	stageSmpBackTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/White.png");
	stageSmpBack = new ShadowUI(oneBuf, stageSmpBackTex);
	stageSmpPos = { 3.5f, 0.0f, SMPBACK_POSZ };
	stageSmpBack->mTransform.pos = stageSmpPos;
	stageSmpBack->mTransform.pos.x += BEGIN_MOVEMENT_X;
	stageSmpBack->mTransform.scale = { 8.0f, 6.0f, 1.0f };
	stageSmpBack->mTransform.rotation.z = SMP_ROT;
	stageSmpBack->MakeDotween();

	smp = new UI(oneBuf, NULL);
	smp->mTransform.rotation.z = SMP_ROT;
	smp->mTransform.scale = { 7.0f,5.25f, 1.0f };

	// 背景
	backGround[0] = new UI(oneBuf, NULL);
	backGround[0]->MakeDotween();
	backGround[0]->mTransform.pos = { 0,0,1.0f };
	backGround[0]->mTransform.pos.z = BG_POSZ;
	backGround[0]->mTransform.scale = { SCREEN_RATIO_W, SCREEN_RATIO_H , 1.0f };

	backGround[1] = new UI(oneBuf, NULL);
	backGround[1]->MakeDotween();
	backGround[1]->mTransform.pos = { backGround[0]->mTransform.pos.x + SCREEN_RATIO_W - 0.25f ,backGround[0]->mTransform.pos.y,  BG_POSZ };
	backGround[1]->mTransform.scale = { SCREEN_RATIO_W, SCREEN_RATIO_H , 0.9f };

	backGround[2] = new UI(oneBuf, NULL);
	backGround[2]->MakeDotween();
	backGround[2]->mTransform.pos = { backGround[0]->mTransform.pos.x + SCREEN_RATIO_W * 2 - 0.5f ,backGround[0]->mTransform.pos.y,  BG_POSZ };
	backGround[2]->mTransform.scale = { SCREEN_RATIO_W, SCREEN_RATIO_H , 0.9f };

	// スタートUI
	D3D_LoadTexture(L"asset/UI/B_Enter.png", &startTex);
	startUI = new ShadowUI(oneBuf, startTex);
	startUI->mTransform.pos = { -6.5f, -4.0f, 0.5f };
	startUI->mTransform.scale = { 2.4f, 0.8f, 1.0f };

	D3D_LoadTexture(L"asset/UI/B_Return.png", &backButtonTex);
	backUI = new ShadowUI(oneBuf, backButtonTex);
	backUI->mTransform.pos = { -4.5f, -4.0f, 0.5f };
	backUI->mTransform.scale = { 2.4f, 0.8f, 1.0f };

	D3D_LoadTexture(L"asset/UI/T_Stage.png", &stageTex);
	stageText = new ShadowUI(oneBuf, stageTex);

	// ステージテキスト
	stageTextPos = { -6.3f, -0.4f, UI_POSZ + UI_OFFSETZ };
	stageText->mTransform.pos = stageTextPos;
	stageText->mTransform.pos.x -= BEGIN_MOVEMENT_X;
	stageText->mTransform.scale = { 2.8f, 0.7f, 1.0f };
	stageText->MakeDotween();

	stageTextBack = new ShadowUI(oneBuf, TextureFactory::GetInstance()->Fetch(L"asset/UI/White.png"));
	stageTextBack->mTransform.pos = stageText->mTransform.pos;
	stageTextBack->mTransform.pos.z += UI_OFFSETZ;
	stageTextBack->mTransform.scale = { 4.0f,0.7f, 1.0f };
	stageTextBack->SetColor({ 245, 96, 149 });

	// World
	D3D_LoadTexture(L"asset/UI/T_World.png", &worldTextTex);
	worldText = new ShadowUI(oneBuf, worldTextTex);
	worldTextPos = { -6.0f, 4.0f, UI_POSZ };
	worldText->mTransform.pos = worldTextPos;
	worldText->mTransform.pos.x = worldTextPos.x - BEGIN_MOVEMENT_X;
	worldText->mTransform.scale = { 3.2f, 0.8f, 1.0f };
	worldText->MakeDotween();

	worldNum = new ShadowUI(numberBuf, numberTex);
	worldNum->mTransform.scale = { 0.8f, 0.8f, 1.0f };
	dynamic_cast<ShadowUI*>(worldNum)->SetShadowOffset({ WORLDNUM_SHADOWOFFSETX, WORLDNUM_SHADOWOFFSETY });


	worldNamePos = { -4.5f, 2.6f, UI_POSZ };
	// ワールド名
	D3D_CreateSquare({ 1,2 }, &worldNameBuffer);
	for (int i = 0; i < 2; i++)
	{
		// テクスチャは各シーン
		worldName[i] = new UI(worldNameBuffer, NULL);
		worldName[i]->mTransform.pos = worldNamePos;
		worldName[i]->mTransform.pos.x -= BEGIN_MOVEMENT_X;
		// 文字をずらす
		worldName[i]->mTransform.pos.y -= i * WORLDNAME_OFFSETY;
		worldName[i]->mTransform.pos.z -= i * UI_OFFSETZ;

		worldName[i]->mTransform.scale = { 6.5f, 1.625f, 1.0f };
		worldName[i]->SetUV(0, i * 0.5f);

		worldName[i]->MakeDotween();

	}

	// 更新
	o_pointStage = c_pointStage;
}

void StageSelect::Update()
{
	if (isBeginFin)
	{
		// 入力
		Input();


		/*static float sinRot = 0.0f;
		sinRot += SIN_SPEED;
		stageSmpBack->mTransform.pos.y = SIN_POWER * sin(DirectX::XMConvertToRadians(sinRot));

		if (sinRot > 360.0f)
		{
			sinRot = 0.0f;
		}*/
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
		worldNum->mTransform.pos.x += WOLRLDNUM_OFFSETX;

		for (int i = 0; i < 2; i++)
		{
			worldName[i]->Update();

		}

	}

	for (int i = 0; i < 3; i++)
	{
		backGround[i]->mTransform.pos.x -= 0.015f;
		if (backGround[i]->mTransform.pos.x < -24.0f)
		{
			backGround[i]->mTransform.pos.x = 22.0f;
		}

	}

	// サンプルの移動処理
	SmpMove();

	stageSmpBack->Update();

	smp->mTransform.pos = stageSmpBack->mTransform.pos;
	smp->mTransform.pos.z -= UI_OFFSETZ;
	smp->SetAlpha(stageSmpBack->materialDiffuse.w);


	for (auto a : stgButton)
	{
		a->Update();
	}

	// 前のステージ番号を更新
	o_pointStage = c_pointStage;
}

void StageSelect::LateUpdate()
{
}

void StageSelect::Draw()
{
	// 背景　→　写真背景　→　写真　→　プレイヤー　→　UI

	backGround[0]->Draw();
	backGround[1]->Draw();
	backGround[2]->Draw();

	stageSmpBack->Draw();

	smp->Draw();

	worldText->Draw();
	worldNum->Draw();


	stageTextBack->Draw();
	stageText->Draw();

	for (int i = 0; i < 2; i++)
	{
		worldName[i]->Draw();
	}

	for (auto a : stgButton)
	{
		a->Draw();
	}

	startUI->Draw();
}

StageSelect::~StageSelect()
{
	SAFE_RELEASE(stageBtnBuf);
	SAFE_RELEASE(stageBtnTex);

	SAFE_RELEASE(numberBuf);
	SAFE_RELEASE(numberTex);

	SAFE_RELEASE(oneBuf);
	CLASS_DELETE(stageSmpBack);
	CLASS_DELETE(backGround[0]);
	CLASS_DELETE(backGround[1]);
	CLASS_DELETE(backGround[2]);
	CLASS_DELETE(btnSelect);

	SAFE_RELEASE(startTex);
	CLASS_DELETE(startUI);
	CLASS_DELETE(backUI);
	SAFE_RELEASE(backButtonTex);

	CLASS_DELETE(stageText);
	SAFE_RELEASE(stageTex);

	CLASS_DELETE(stageTextBack);

	CLASS_DELETE(worldText);
	SAFE_RELEASE(worldTextTex)


		CLASS_DELETE(worldNum);

	SAFE_RELEASE(backTex);

	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(worldName[i]);
	}
	SAFE_RELEASE(worldNameBuffer);
	SAFE_RELEASE(worldNameTex);

	CLASS_DELETE(smp);
	
	for (auto a : stageSmpTex)
	{
		SAFE_RELEASE(a);
	}
}

void StageSelect::BeginMove()
{
	stageText->dotween->DoEaseOutBack(stageTextPos, BEGIN_MOVETIME);
	stageText->dotween->OnComplete([&]()
		{
			isBeginFin = true;
		});

	stageSmpBack->dotween->DoEaseOutBack(stageSmpPos, BEGIN_MOVETIME);

	worldText->dotween->DoEaseOutBack(worldTextPos, BEGIN_MOVETIME);

	for (int i = 0; i < 2; i++)
	{
		Vector3 v = worldNamePos;
		v.x += i * worldNameOffsetX;
		v.y -= i * WORLDNAME_OFFSETY;
		v.z -= i * UI_OFFSETZ;
		worldName[i]->dotween->DoEaseOutBack(v, BEGIN_MOVETIME);
	}

	// ボタンの移動
	for (int i = 0; i < stgButton.size(); i++)
	{
		// 移動先の座標
		Vector3 p = firstBtnPos;
		p.x += i * BTN_OFFSETX * btnScale.x;

		// 動かす
		stgButton[i]->GetDotween()->DoEaseOutBack(p, BEGIN_MOVETIME);
	}
}
