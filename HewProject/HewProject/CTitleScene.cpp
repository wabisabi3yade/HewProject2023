#include "CTitleScene.h"
#include "CSceneManager.h"
#include "InputManager.h"
#include "UI.h"
#include "TextureFactory.h"
#include <random>
#include "ButtonUI.h"
#include "CTitlePlayer.h"

#define MIN -9
#define MAX 9

#define BEGIN_POSZ (0.31f)	// ケーキ一番奥の座標

CTitleScene::CTitleScene()
{
	D3D_CreateSquare({ 1,1 }, &selectBuffer);
	selectTexture = TextureFactory::GetInstance()->Fetch(L"asset/Stage/Castella.png");

	D3D_CreateSquare({ 1,2 }, &buttonBuffer);
	buttonTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_GameStart.png");
	text_endTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_GameEnd.png");

	select[0] = new ButtonUI(buttonBuffer, buttonTexture, textBuffer, textTexture);
	select[0]->SetPosition({ -2.5f,-3.0f,-0.2f });
	select[0]->SetScale({ 4,4,1 });

	select[1] = new ButtonUI(buttonBuffer, buttonTexture, textBuffer, text_endTexture);
	select[1]->SetPosition({ 2.5f,-3.0f,-0.2f });
	select[1]->SetScale({ 4,4,1 });

	select[0]->SetHighlight(true);

	D3D_CreateSquare({ 1,1 }, &sweetsBuffer);
	sweetsTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/Cake.png");

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(MIN, MAX);

	for (int i = 0; i < MAXNUM_CAKE; i++)
	{
		if (i < 5)
		{
			Sweets[i] = new UI(sweetsBuffer, sweetsTexture);
			Sweets[i]->MakeDotween();
			Sweets[i]->mTransform.pos = { distr(eng),5.0f + i * 0.4f,BEGIN_POSZ - i * 0.001f };
			Sweets[i]->mTransform.scale = { 3.0f,3.0f,1.0f };
			Sweets[i]->mTransform.rotation = { 0,0,45.0f + i * 30.0f };
			Sweets[i]->materialDiffuse = { 1,1,1,1 };
		}
		else if (i < 10)
		{
			Sweets[i] = new UI(sweetsBuffer, sweetsTexture);
			Sweets[i]->MakeDotween();
			Sweets[i]->mTransform.pos = { distr(eng),5.3f + i % 5 * 0.4f,BEGIN_POSZ - i * 0.001f };
			Sweets[i]->mTransform.scale = { 3.0f,3.0f,1.0f };
			Sweets[i]->mTransform.rotation = { 0,0,45.0f + i * 30.0f };
			Sweets[i]->materialDiffuse = { 1,1,1,1 };
		}
		/*else if (i < 15)
		{
			Sweets[i] = new UI(selectBuffer, selectTexture);
			Sweets[i]->MakeDotween();
			Sweets[i]->mTransform.pos = { distr(eng),5.6f + i % 5 * 0.4f,BEGIN_POSZ - i * 0.001f };
			Sweets[i]->mTransform.scale = { 3.0f,3.0f,1.0f };
			Sweets[i]->mTransform.rotation = { 0,0,45.0f + i * 30.0f };
			Sweets[i]->materialDiffuse = { 1,1,1,1 };
		}
		else {
			Sweets[i] = new UI(selectBuffer, selectTexture);
			Sweets[i]->MakeDotween();
			Sweets[i]->mTransform.pos = { distr(eng),5.9f + i % 5 * 0.4f,BEGIN_POSZ - i * 0.001f };
			Sweets[i]->mTransform.scale = { 3.0f,3.0f,1.0f };
			Sweets[i]->mTransform.rotation = { 0,0,45.0f + i * 30.0f };
			Sweets[i]->materialDiffuse = { 1,1,1,1 };
		}*/

	}

	D3D_CreateSquare({ 1,1 }, &titleBuffer);
	titleTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Title.png");

	Title = new UI(titleBuffer, titleTexture);
	Title->MakeDotween();
	Title->mTransform.pos = { 0,8.0f,0.3f };
	Title->mTransform.scale = { 8,8,1 };
	Title->materialDiffuse = { 1,1,1,1 };

	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/Background/Stage2.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->mTransform.pos = { 0,0,0.5f };
	Bg->mTransform.scale = { 16,9,1 };
	Bg->materialDiffuse = { 1,1,1,1 };

	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	player_normalTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Walk.png");
	player_fatTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/F_Walk.png");
	player_thinTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_Walk.png");

	srand(time(NULL));
	nRandom = rand() % 3;
	
	player[0] = new CTitlePlayer(playerBuffer, player_normalTexture);
	player[0]->mTransform.scale = {2,2,1};
	player[0]->isNormal = false;
	player[0]->isFat = true;
	player[0]->isThin = true;
	player[0]->isAll = true;
	player[0]->nRandomChara = nRandom;
	
	player[1] = new CTitlePlayer(playerBuffer, player_fatTexture);
	player[1]->mTransform.pos = { 4.0f,5.0f,-0.11f };
	player[1]->mTransform.scale = { 2,2,1 };
	player[1]->isNormal = true;
	player[1]->isFat = false;
	player[1]->isThin = true;
	player[1]->isAll = true;
	player[1]->nRandomChara = nRandom;

	player[2] = new CTitlePlayer(playerBuffer, player_thinTexture);
	player[2]->mTransform.pos = { -4.0f,-5.0f,-0.12f };
	player[2]->mTransform.scale = { 2,2,1 };
	player[2]->isNormal = true;
	player[2]->isFat = true;
	player[2]->isThin = false;
	player[2]->isAll = true;
	player[2]->nRandomChara = nRandom;

	player[3] = new CTitlePlayer(playerBuffer, player_normalTexture);
	player[3]->mTransform.pos = { -9.0f,-5.0f,-0.13f };
	player[3]->mTransform.scale = { 2,2,1 };
	player[3]->isNormal = true;
	player[3]->isFat = true;
	player[3]->isThin = true;
	player[3]->isAll = false;
	player[3]->nRandomChara = nRandom;

	isNoMoving = false;
	isOnce = false;
	isRotationSwitch = false;
	isFlash = false;

}

CTitleScene::~CTitleScene()
{
	CLASS_DELETE(Title);

	CLASS_DELETE(Bg);

	for (int i = 0; i < MAXNUM_PLAYER; i++)
	{
		CLASS_DELETE(player[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(select[i]);
	}

	for (int i = 0; i < MAXNUM_CAKE; i++)
	{
		CLASS_DELETE(Sweets[i]);
	}
}

void CTitleScene::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	Title->Update();

	Bg->Update();

	for (int i = 0; i < MAXNUM_CAKE; i++)
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
			Title->dotween->DoMoveY(1.5f, 3.0f);
			isOnce = true;
		}

		Title->dotween->OnComplete([&]()
			{
				isNoMoving = true;
			});

	}
	else {

		if (isOnce == true)
		{
			isOnce = false;

			for (int i = 0; i < MAXNUM_CAKE; i++)
			{
				if (i < 5)
				{
					Sweets[i]->dotween->DoMoveY(-8.2f, 6.0f);
					Sweets[i]->dotween->OnComplete([&]() {

						std::random_device rd;
						std::default_random_engine eng(rd());
						std::uniform_real_distribution<float> distr(MIN, MAX);
						//Sweets[i]->mTransform.pos = { 9.0f,distr(eng),BEGIN_POSZ - i * 0.001f };

						});
					//Sweets[i]->dotween->Join(360.0f, 3.0f, DoTweenUI::FUNC::ROTATION);
				}
				else if (i < 10)
				{
					Sweets[i]->dotween->DoMoveY(-8.5f, 8.0f);
					Sweets[i]->dotween->OnComplete([&]() {

						std::random_device rd;
						std::default_random_engine eng(rd());
						std::uniform_real_distribution<float> distr(MIN, MAX);
						//Sweets[i]->mTransform.pos = { 9.0f,distr(eng),BEGIN_POSZ - i * 0.001f };

						});
					//Sweets[i]->dotween->Join(360.0f, 4.0f, DoTweenUI::FUNC::ROTATION);
				}
				/*else if (i < 15)
				{
					Sweets[i]->dotween->DoMoveY(-8.8f, 4.0f);
					Sweets[i]->dotween->Join(360.0f, 4.0f, DoTweenUI::FUNC::ROTATION);
				}
				else
				{
					Sweets[i]->dotween->DoMoveY(-8.1f, 4.0f);
					Sweets[i]->dotween->Join(360.0f, 4.0f, DoTweenUI::FUNC::ROTATION);
				}*/

				
			}

		}

		for (int i = 0; i < MAXNUM_CAKE; i++)
		{
			Sweets[i]->mTransform.rotation.z += 0.5f;
		}

		for (int i = 0; i < MAXNUM_PLAYER; i++)
		{
			if (player[i]->isStopMove == true)
			{
				player[i]->nRandomChara = nRandom = rand() % 3;

				switch (player[i]->nRandomChara)
				{
				case 0:
					player[i]->SetTexture(player_normalTexture);
					player[i]->isStopMove = false;
					player[i]->nAction = rand() % 4;
					break;
				case 1:
					player[i]->SetTexture(player_fatTexture);
					player[i]->isStopMove = false;
					player[i]->nAction = rand() % 4;
					break;
				case 2:
					player[i]->SetTexture(player_thinTexture);
					player[i]->isStopMove = false;
					player[i]->nAction = rand() % 4;
					break;
				default:
					break;
				}
			}
		}
		
		
		for (int i = 0; i < MAXNUM_PLAYER; i++)
		{
			player[i]->Update();
		}
		
		if (input->GetInputTrigger(InputType::DECIDE) && isFlash == false)
		{
			CScene::SetScene(SCENE_NAME::WAKAMURA);
		}
		else if (input->GetInputTrigger(InputType::DECIDE) && isFlash == true)
		{
			exit(1);
		}

		if (input->GetMovement().x < 0)
		{
			isFlash = false;
			select[0]->SetHighlight(true);
			select[1]->SetHighlight(false);
		}
		if (input->GetMovement().x > 0)
		{
			isFlash = true;
			select[0]->SetHighlight(false);
			select[1]->SetHighlight(true);
		}
	}
}

void CTitleScene::LateUpdate()
{
}

void CTitleScene::Draw()
{
	Bg->Draw();

	if (isNoMoving == true)
	{
		for (int i = 0; i < MAXNUM_PLAYER; i++)
		{
			player[i]->Draw();
		}

		for (int i = 0; i < MAXNUM_CAKE; i++)
		{
			Sweets[i]->Draw();
		}

		select[0]->Draw();
		select[1]->Draw();
	}
	
	Title->Draw();

}
