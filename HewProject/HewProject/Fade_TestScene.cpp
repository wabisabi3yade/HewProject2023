#include "Fade_TestScene.h"
#include "Fade.h"
#include "CalorieGage_hori.h"
#include "TextureFactory.h"

Fade_TestScene::Fade_TestScene()
{
	fade = Fade::GetInstance();
	gage = new CalorieGage_hori();

	gage->SetScale({0.5f, 0.5f,1.0f});
	gage->SetPosition({ 3.0,3.0f,1.0f });
}

Fade_TestScene::~Fade_TestScene()
{
	CLASS_DELETE(gage);
}

void Fade_TestScene::Update()
{
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

	gage->Update();
}

void Fade_TestScene::LateUpdate()
{
}

void Fade_TestScene::Draw()
{
	gage->Draw();
}
