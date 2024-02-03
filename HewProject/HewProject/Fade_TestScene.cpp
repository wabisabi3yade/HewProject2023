#include "Fade_TestScene.h"
#include "Fade.h"
#include "CalorieGage_hori.h"
#include "TextureFactory.h"
#include "FloorUI.h"
#include "ButtonUI.h"
#include "ProteinUI.h"

Fade_TestScene::Fade_TestScene()
{
	fade = Fade::GetInstance();
	gage = new CalorieGage_hori();

	floorUI = new FloorUI(1, 3);

	gage->SetScale({0.5f, 0.5f,1.0f});
	gage->SetPosition({ 3.0,3.0f,1.0f });

	D3D_CreateSquare({ 1,2 }, &buffer);
	D3DTEXTURE texWork = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");
	buttonUI = new ButtonUI(buffer, texWork);
	buttonUI->mTransform.scale = { 2.0f, 0.5f, 1.0f };

	proteinUI = new ProteinUI(2);
	proteinUI->SetPosition({ 2.0f, 2.0f, 0.0f });
}

Fade_TestScene::~Fade_TestScene()
{
	CLASS_DELETE(gage);
}

void Fade_TestScene::Update()
{
	static int a = 1;

	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		fade->FadeIn(Fade::STATE::LOADING);
	}
	else if (gInput->GetKeyTrigger(VK_SPACE))
	{
		fade->FadeIn(Fade::STATE::FADE_OUT);
	}

	else if (gInput->GetKeyTrigger(VK_UP))
	{
		gage->AddCalorie(1);
	}

	else if (gInput->GetKeyTrigger(VK_DOWN))
	{
		gage->AddCalorie(-1);
	}

	else if (gInput->GetKeyTrigger(VK_LEFT))
	{
		gage->SetCalorie(15);
	}

	else if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		gage->SetCalorie(5,false);
	}
	
	else if (gInput->GetKeyTrigger(VK_F1))
	{
		a++;
		floorUI->SetHighlight(a);
	}

	else if (gInput->GetKeyTrigger(VK_F2))
	{
		a--;
		floorUI->SetHighlight(a);
	}

	if (gInput->GetKeyTrigger(VK_F3))
	{
		buttonUI->SetHighlight(true);
	}
	else if (gInput->GetKeyTrigger(VK_F4))
	{
		buttonUI->SetHighlight(false);
	}

	if (gInput->GetKeyTrigger(VK_F5))
	{
		proteinUI->SetProtein(0);
	}
	else if (gInput->GetKeyTrigger(VK_F6))
	{
		proteinUI->AddProtein();
	}

	gage->Update();
	proteinUI->Update();
}

void Fade_TestScene::LateUpdate()
{
}

void Fade_TestScene::Draw()
{
	gage->Draw();

	floorUI->Draw();

	/*buttonUI->Draw();*/

	proteinUI->Draw();
}
