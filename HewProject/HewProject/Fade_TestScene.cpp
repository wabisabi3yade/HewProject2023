#include "Fade_TestScene.h"
#include "Fade.h"

Fade_TestScene::Fade_TestScene()
{
	fade = Fade::GetInstance();

	calorieGage = new CalorieGage();
}

Fade_TestScene::~Fade_TestScene()
{
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

	calorieGage->Update();
}

void Fade_TestScene::LateUpdate()
{
}

void Fade_TestScene::Draw()
{
	calorieGage->Draw();
}
