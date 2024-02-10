#include "StageSelect.h"
#include "ButtonSelect.h"
#include "InputManager.h"

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
	// ƒ{ƒ^ƒ“”wŒi
	D3D_CreateSquare({ 2,1 }, &stageBtnBuf);
	D3D_LoadTexture(L"asset/UI/StageSelect_Btn.png", &stageBtnTex);
	// ”Žš
	D3D_CreateSquare({ 3,4 }, &numberBuf);
	D3D_LoadTexture(L"asset/UI/Calorie_Number.png", &numberTex);

	btnSelect = new ButtonSelect();
}

void StageSelect::Update()
{

	Input();

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
}

StageSelect::~StageSelect()
{
	SAFE_RELEASE(stageBtnBuf);
	SAFE_RELEASE(stageBtnTex);

	SAFE_RELEASE(numberBuf);
	SAFE_RELEASE(numberTex);

	CLASS_DELETE(btnSelect);
}
