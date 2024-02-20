#include "CTitleScene.h"
#include "CSceneManager.h"
#include "InputManager.h"
#include "TextureFactory.h"
#include <random>
#include "ButtonUI.h"
#include "CTitlePlayer.h"
#include"SweetsUI.h"
#include "ButtonSelect.h"
#include <time.h>

#define MIN -8
#define BETWEEN 0
#define MAX 8

#define BEGIN_POSZ (0.32f)	// ケーキ一番奥の座標
#define SWEETS_SCALE (2.0f)
#define BAUM_SCALE (1.5f)

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
	select[0]->SetFunc([&]()
		{

			Title->dotween->DelayedCall(0.5f, [&]()
				{
					if (Fade::GetInstance()->GetState() != Fade::STATE::STAY) return;
					Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, nullptr, CScene::SCENE_NAME::STAGE1);
				});
			
		});

	select[1] = new ButtonUI(buttonBuffer, buttonTexture, textBuffer, text_endTexture);
	select[1]->SetPosition({ 2.5f,-3.0f,-0.2f });
	select[1]->SetScale({ 4,4,1 });
	select[1]->SetFunc([&]()
		{
			Title->dotween->DelayedCall(2.0f, [&]()
				{
					// 終了
					Exit();
				});
		});

	select[0]->SetHighlight(true);

	// ボタン選択クラス作成
	selectControl = new ButtonSelect();
	selectControl->Regist(select[0]);
	selectControl->Regist(select[1]);

	D3D_CreateSquare({ 1,1 }, &sweetsBuffer);
	sweetsTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/FallCake.png");
	D3D_LoadTexture(L"asset/Stage/Baumkuchen_L.png" ,&baumTexture);
	D3D_LoadTexture(L"asset/Item/Protein.png", &proteinTexture);

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(MIN, MAX);

	for (int i = 0; i < MAXNUM_CAKE; i++)
	{
		if (i < 5)
		{
			Sweets[i] = new SweetsUI(sweetsBuffer, baumTexture);
			Sweets[i]->SetPosition({ distr(eng),6.0f + i * 2.0f,BEGIN_POSZ - i * 0.001f });
			Sweets[i]->SetScale({ 1.0f,1.0f,1.0f });
			Sweets[i]->SetRotation({ 0,0,45.0f + i * 30.0f });
		}
		else
		{
			Sweets[i] = new SweetsUI(sweetsBuffer, proteinTexture);
			Sweets[i]->SetPosition({ distr(eng),7.3f + i * 2.0f,BEGIN_POSZ - i * 0.001f });
			Sweets[i]->SetScale({ 1.0f, 1.0f, 1.0f });
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
	bg_Stage1Texture = TextureFactory::GetInstance()->Fetch(L"asset/Background/Stage1.png");
	bg_Stage2Texture = TextureFactory::GetInstance()->Fetch(L"asset/Background/Stage2.png");
	bg_Stage3Texture = TextureFactory::GetInstance()->Fetch(L"asset/Background/Stage3.png");
	bg_StageEXTexture = TextureFactory::GetInstance()->Fetch(L"asset/Background/StageEX.png");

	Bg = new UI(bgBuffer, bg_Stage1Texture);
	Bg->mTransform.pos = { 0,0,0.5f };
	Bg->mTransform.scale = { 16,9,1 };
	Bg->materialDiffuse = { 1,1,1,1 };

	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	player_normalTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Walk.png");
	player_fatTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/F_Walk.png");
	player_thinTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_Walk.png");

	srand(time(NULL));
	nRandom = rand() % 3;
	nRandom_Bg = rand() % 4;
	
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

	D3D_CreateSquare({ 1,1 }, &A_ButtonBuffer);
	D3D_LoadTexture(L"asset/UI/B_Enter.png", &A_ButtonTexture);

	A_Button = new UI(A_ButtonBuffer, A_ButtonTexture);
	A_Button->mTransform.pos = { -6.5f,-4.0f,-0.3f };
	A_Button->mTransform.scale = { 2.4f,0.8f,1.0f };

	isNoMoving = false;
	isOnce = false;
	
	// BGM流す
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_Title);

}

CTitleScene::~CTitleScene()
{
	CLASS_DELETE(Title);

	CLASS_DELETE(Bg);

	CLASS_DELETE(A_Button);

	for (int i = 0; i < MAXNUM_PLAYER; i++)
	{
		CLASS_DELETE(player[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(select[i]);
	}
	
	CLASS_DELETE(selectControl);

	for (int i = 0; i < MAXNUM_CAKE; i++)
	{
		CLASS_DELETE(Sweets[i]);
	}

	SAFE_RELEASE(titleBuffer);
	SAFE_RELEASE(bgBuffer);
	SAFE_RELEASE(sweetsBuffer);
	SAFE_RELEASE(selectBuffer);
	SAFE_RELEASE(buttonBuffer);
	SAFE_RELEASE(textBuffer);
	SAFE_RELEASE(playerBuffer);
	SAFE_RELEASE(baumTexture);
	SAFE_RELEASE(proteinTexture);
	SAFE_RELEASE(A_ButtonBuffer);
	SAFE_RELEASE(A_ButtonTexture);
}

void CTitleScene::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	Title->Update();

	Bg->Update();

	A_Button->Update();

	for (int i = 0; i < 2; i++)
	{
		select[i]->Update();
	}

	if (isNoMoving == false)
	{
		switch (nRandom_Bg)
		{
		case 0:
			Bg->SetTexture(bg_Stage1Texture);
			break;
		case 1:
			Bg->SetTexture(bg_Stage2Texture);
			break;
		case 2:
			Bg->SetTexture(bg_Stage3Texture);
			break;
		case 3:
			Bg->SetTexture(bg_StageEXTexture);
			break;
		default:
			break;
		}

		if (isOnce == false)
		{
			Title->dotween->DoMoveY(1.5f, 3.0f);
			isOnce = true;
		}

		Title->dotween->OnComplete([&]()
			{
				isNoMoving = true;
				for (int i = 0; i < MAXNUM_CAKE; i++)
				{
					RandomSweets(i);
				}
				
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

				RandomSweets(i);

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
		

		if (input->GetInputTrigger(InputType::DECIDE))
		{
			XA_Play(SOUND_LABEL::S_PUSH_STAGEBTN);
			selectControl->PushButton(true);
		}


		selectControl->FlagUpdate();
		if (input->GetMovement().x < 0)
		{
			selectControl->ButtonMove(-1);
		}
		if (input->GetMovement().x > 0)
		{
			selectControl->ButtonMove(1);
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

		A_Button->Draw();
	}
	
	Title->Draw();
}

void CTitleScene::RandomSweets(int _num)
{
	nRandom = rand() % 3;

	switch (nRandom)
	{
	case 0:
		Sweets[_num]->SetTexture(sweetsTexture);
		Sweets[_num]->SetScale({ SWEETS_SCALE,SWEETS_SCALE,1.0f });
		break;
	case 1:
		Sweets[_num]->SetTexture(baumTexture);
		Sweets[_num]->SetScale({ BAUM_SCALE,BAUM_SCALE,1.0f });
		break;
	case 2:
		Sweets[_num]->SetTexture(proteinTexture);
		Sweets[_num]->SetScale({ SWEETS_SCALE,SWEETS_SCALE,1.0f });
		break;
	default:
		break;
	}
}
