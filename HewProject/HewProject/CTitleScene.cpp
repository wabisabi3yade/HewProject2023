#include "CTitleScene.h"
#include "CSceneManager.h"
#include "InputManager.h"
#include "TextureFactory.h"
#include <random>
#include "ButtonUI.h"
#include "CTitlePlayer.h"
#include"SweetsUI.h"

#define MIN -8
#define BETWEEN 0
#define MAX 8

#define BEGIN_POSZ (0.32f)	// ケーキ一番奥の座標

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
			Sweets[i] = new SweetsUI(sweetsBuffer, sweetsTexture);
			Sweets[i]->SetPosition({ distr(eng),6.0f + i * 2.0f,BEGIN_POSZ - i * 0.001f });
			Sweets[i]->SetScale({ 3.0f,3.0f,1.0f });
			Sweets[i]->SetRotation({ 0,0,45.0f + i * 30.0f });
		}
		else
		{
			Sweets[i] = new SweetsUI(sweetsBuffer, sweetsTexture);
			Sweets[i]->SetPosition({ distr(eng),7.3f + i * 2.0f,BEGIN_POSZ - i * 0.001f });
			Sweets[i]->SetScale({ 3.0f, 3.0f, 1.0f });
			Sweets[i]->SetRotation({ 0,0,45.0f + i * 30.0f });
		}
		
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

		for (int i = 0; i < MAXNUM_CAKE; i++)
		{
			if (i == 0 || i == 1)
			{
				Sweets[i]->SetPosSpeed(-5.5f, 15.0f);
			}
			else if(i == 2 || i == 3){
				Sweets[i]->SetPosSpeed(-6.0f, 18.0f);
			}
			else if (i == 4 || i == 5)
			{
				Sweets[i]->SetPosSpeed(-6.5f, 20.0f);
			}
			else if (i == 6 || i == 7)
			{
				Sweets[i]->SetPosSpeed(-7.5f, 22.0f);
			}
			else if (i == 8 || i == 9 ||i == MAXNUM_CAKE)
			{
				Sweets[i]->SetPosSpeed(-8.0f, 25.0f);
			}


			if (Sweets[i]->isResporn == true)
			{
				std::random_device rd;
				std::default_random_engine eng(rd());
				std::uniform_real_distribution<float> distr_min(MIN, BETWEEN);
				std::uniform_real_distribution<float> distr_max(BETWEEN,MAX);

				if (i % 2 == 0)
				{
					Sweets[i]->vCopy = { distr_min(eng),6.0f + i * 1.0f,BEGIN_POSZ - i * 0.001f };
					Sweets[i]->SetPosition({ Sweets[i]->vCopy });
				}
				else if(i % 2 == 1)
				{
					Sweets[i]->vCopy = { distr_max(eng),6.0f + i * 1.0f,BEGIN_POSZ - i * 0.001f };
					Sweets[i]->SetPosition({ Sweets[i]->vCopy });
				}

				Sweets[i]->isResporn = false;
			}

			Sweets[i]->SetRotateZ(1.5f);
			

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
		
		for (int i = 0; i < MAXNUM_CAKE; i++)
		{
			Sweets[i]->Update();
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
