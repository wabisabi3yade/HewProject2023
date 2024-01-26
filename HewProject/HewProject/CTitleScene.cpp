#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CInput.h"
#include "UI.h"
#include "TextureFactory.h"
#include <random>
#include <iostream>
#include <algorithm>

#define MIN -1
#define MAX 1

#define BEGIN_POSZ (0.1f)	// ケーキ一番奥の座標

CTitleScene::CTitleScene()
{
	D3D_CreateSquare({ 1,1 }, &sweetsBuffer);
	sweetsTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/Cake.png");

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(MIN, MAX);

	for (int i = 0; i < MAXNUM; i++)
	{
		if (i < 5)
		{
			Sweets[i] = new UI(sweetsBuffer, sweetsTexture);
			Sweets[i]->MakeDotween();
			Sweets[i]->mTransform.pos = { distr(eng),2.0f + i * 0.4f,BEGIN_POSZ - i * 0.001f };
			Sweets[i]->mTransform.scale = { 0.7f,0.7f,1.0f };
			Sweets[i]->mTransform.rotation = { 0,0,45.0f + i * 30.0f };
			Sweets[i]->materialDiffuse = { 1,1,1,1 };
		}
		else if (i < 10)
		{
			Sweets[i] = new UI(sweetsBuffer, sweetsTexture);
			Sweets[i]->MakeDotween();
			Sweets[i]->mTransform.pos = { distr(eng),2.3f + i % 5 * 0.4f,BEGIN_POSZ - i * 0.001f };
			Sweets[i]->mTransform.scale = { 0.7f,0.7f,1.0f };
			Sweets[i]->mTransform.rotation = { 0,0,45.0f + i * 30.0f };
			Sweets[i]->materialDiffuse = { 1,1,1,1 };
		}
		else if (i < 15)
		{
			Sweets[i] = new UI(sweetsBuffer, sweetsTexture);
			Sweets[i]->MakeDotween();
			Sweets[i]->mTransform.pos = { distr(eng),2.6f + i % 5 * 0.4f,BEGIN_POSZ - i * 0.001f };
			Sweets[i]->mTransform.scale = { 0.7f,0.7f,1.0f };
			Sweets[i]->mTransform.rotation = { 0,0,45.0f + i * 30.0f };
			Sweets[i]->materialDiffuse = { 1,1,1,1 };
		}
		else {
			Sweets[i] = new UI(sweetsBuffer, sweetsTexture);
			Sweets[i]->MakeDotween();
			Sweets[i]->mTransform.pos = { distr(eng),2.9f + i % 5 * 0.4f,BEGIN_POSZ - i * 0.001f };
			Sweets[i]->mTransform.scale = { 0.7f,0.7f,1.0f };
			Sweets[i]->mTransform.rotation = { 0,0,45.0f + i * 30.0f };
			Sweets[i]->materialDiffuse = { 1,1,1,1 };
		}

	}

	D3D_CreateSquare({ 1,1 }, &titleBuffer);
	titleTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Title.png");

	Title = new UI(titleBuffer, titleTexture);
	Title->MakeDotween();
	Title->mTransform.pos = { 0,1.5f,0.3f };
	Title->mTransform.scale = { 1,1.2,1 };
	Title->materialDiffuse = { 1,1,1,1 };

	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/fade_BackBlue.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->mTransform.pos = { 0,0,0.4f };
	Bg->mTransform.scale = { 3,4,1 };
	Bg->materialDiffuse = { 1,1,1,1 };

	D3D_CreateSquare({ 1,1 }, &selectBuffer);
	selectTexture = TextureFactory::GetInstance()->Fetch(L"asset/Stage/Castella.png");

	for (int i = 0; i < 2; i++)
	{
		select[i] = new CGridObject(selectBuffer, selectTexture);
		select[i]->mTransform.pos = { -2.5f + i * 5.0f,-1.0f,0.3f };
		select[i]->mTransform.scale = { 2,2,1 };
	}
	

	isNoMoving = false;
	isOnce = false;
	isRotationSwitch = false;
	isFlash = false;

	m_DrawCount = 0;
}

CTitleScene::~CTitleScene()
{
	CLASS_DELETE(Title);

	CLASS_DELETE(Bg);

	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(select[i]);
	}

	for (int i = 0; i < MAXNUM; i++)
	{
		CLASS_DELETE(Sweets[i]);
	}
}

void CTitleScene::Update()
{
	Title->Update();

	Bg->Update();

	for (int i = 0; i < MAXNUM; i++)
	{
		Sweets[i]->Update();
	}

	for (int i = 0; i < 2; i++)
	{
		select[i]->Update();
	}

	if (isNoMoving == false)
	{
		if (isOnce == false)
		{
			for (int i = 0; i < MAXNUM; i++)
			{
				if (i < 5)
				{
					Sweets[i]->dotween->DoMoveY(-1.2f, 3.0f);
					Sweets[i]->dotween->Join(360.0f, 3.0f, DoTweenUI::FUNC::ROTATION);
				}
				else {
					Sweets[i]->dotween->DoMoveY(-1.5f, 4.0f);
					Sweets[i]->dotween->Join(360.0f, 4.0f, DoTweenUI::FUNC::ROTATION);
				}
			}

			Title->dotween->DoMoveY(0.5f, 3.0f);
			isOnce = true;
		}

		Title->dotween->OnComplete([&]()
			{
				isNoMoving = true;
			});

	}
	else {

		if (isRotationSwitch == false)
		{
			Title->mTransform.rotation.z += 1.0f;
			if (Title->mTransform.rotation.z > 45.0f)
			{
				isRotationSwitch = true;
			}
		}
		else
		{
			Title->mTransform.rotation.z -= 1.0f;
			if (Title->mTransform.rotation.z < -45.0f)
			{
				isRotationSwitch = false;
			}
		}

		if (gInput->GetKeyTrigger(VK_RETURN) && isFlash == false)
		{
			CScene::SetScene(SCENE_NAME::WAKAMURA);
		}
		else if (gInput->GetKeyTrigger(VK_RETURN) && isFlash == true)
		{
			exit(1);
		}

		if (gInput->GetKeyTrigger(VK_LEFT))
		{
			isFlash = false;
		}
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			isFlash = true;
		}
	}
}

void CTitleScene::LateUpdate()
{
}

void CTitleScene::Draw()
{
	Bg->Draw();

	Title->Draw();

	if (isNoMoving == true)
	{
		if (isFlash == false)
		{
			if (m_DrawCount % 8 == 0)
			{
				select[0]->Draw();
			}
			
			select[1]->Draw();
		}
		else {
			if (m_DrawCount % 8 == 0)
			{
				select[1]->Draw();
			}
			select[0]->Draw();
		}

		++m_DrawCount;
		
	}
	
	for (int i = 0; i < MAXNUM; i++)
	{
		Sweets[i]->Draw();
	}
}
