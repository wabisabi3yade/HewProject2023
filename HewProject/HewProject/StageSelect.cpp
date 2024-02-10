#include "StageSelect.h"
#include "ButtonSelect.h"
#include "InputManager.h"
#include "TextureFactory.h"

void StageSelect::Input()
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
	else if (input->GetMovement().y < 0.0f)
	{
		btnSelect->ButtonMove(3);
	}
	else if (input->GetMovement().y > 0.0f)
	{
		btnSelect->ButtonMove(-3);
	}
}

StageSelect::StageSelect()
{
	// ボタン背景
	D3D_CreateSquare({ 2,1 }, &stageBtnBuf);
	D3D_LoadTexture(L"asset/UI/StageSelect_Btn.png", &stageBtnTex);
	// 数字
	D3D_CreateSquare({ 3,4 }, &numberBuf);
	D3D_LoadTexture(L"asset/UI/Calorie_Number.png", &numberTex);

	btnSelect = new ButtonSelect();

	D3D_CreateSquare({ 1,1 }, &oneBuf);
	stageSmpBackTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/White.png");

	stageSmpBack = new UI(oneBuf, stageSmpBackTex);
	stageSmpBack->MakeDotween();
	stageSmpBack->mTransform.scale = { 9.33f, 7.0f, 1.0f };
}

void StageSelect::Update()
{
	Input();

	stageSmpBack->Update();

	for (auto a : stgButton)
	{
		a->Update();
	}
}

void StageSelect::LateUpdate()
{
}

void StageSelect::Draw()
{
	// 背景　→　写真背景　→　写真　→　プレイヤー　→　UI

	stageSmpBack->Draw();

	for (auto a : stgButton)
	{
		a->Draw();
	}
}

StageSelect::~StageSelect()
{
	SAFE_RELEASE(stageBtnBuf);
	SAFE_RELEASE(stageBtnTex);

	SAFE_RELEASE(numberBuf);
	SAFE_RELEASE(numberTex);

	SAFE_RELEASE(oneBuf);
	CLASS_DELETE(stageSmpBack);

	CLASS_DELETE(btnSelect);
}
