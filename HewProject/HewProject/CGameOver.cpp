#include "CGameOver.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"
#include "CWorldSelectPlayer.h"
#include "ButtonUI.h"
#include "ButtonSelect.h"

CGameOver::CGameOver()
{
	D3D_CreateSquare({ 7,1 }, &text_failedBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/GAMEOVER.png");

	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->materialDiffuse = { 1,1,1,0 };
	Bg->mTransform.pos = { 0,0,0.1f };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		Text[i] = new UI(text_failedBuffer, textTexture);
		Text[i]->MakeDotween();
	}

	D3D_CreateSquare({ 1,2 }, &textBoxBuffer);
	textBoxTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_restartTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Restart.png");
	text_undoTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Undo.png");
	text_backTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Back.png");

	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_Wait.png");


	Text[0]->mTransform.pos = { -3.5f,6.0f,0 };
	Text[0]->mTransform.scale = { 1.0f,1.0f,1.0f };

	Text[1]->mTransform.pos = { -2.5f,6.0f,0 };
	Text[1]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[1]->SetUV(1.0f/7.0f*1.0f,0);

	Text[2]->mTransform.pos = { -1.5f,6.0f,0 };
	Text[2]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[2]->SetUV(1.0f / 7.0f * 2.0f, 0);

	Text[3]->mTransform.pos = { -0.5f,6.0f,0 };
	Text[3]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[3]->SetUV(1.0f / 7.0f * 3.0f, 0);

	Text[4]->mTransform.pos = { 0.5f,6.0f,0 };
	Text[4]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[4]->SetUV(1.0f / 7.0f * 4.0f, 0);

	Text[5]->mTransform.pos = { 1.5f,6.0f,0 };
	Text[5]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[5]->SetUV(1.0f / 7.0f * 5.0f, 0);

	Text[6]->mTransform.pos = { 2.5f,6.0f,0 };
	Text[6]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[6]->SetUV(1.0f / 7.0f * 3.0f, 0);

	Text[7]->mTransform.pos = { 3.5f,6.0f,0 };
	Text[7]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[7]->SetUV(1.0f / 7.0f * 6.0f, 0);

	Message[0] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_restartTexture);
	Message[0]->SetPosition({ -5.0f,-3.0f,0 });
	Message[0]->SetScale({ 4.0f,4.0f,1.0f });
	Message[0]->SetHighlight(true);
	Message[0]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::SELECT);
		});

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_undoTexture);
	Message[1]->SetPosition({ 0,-3.0f,0 });
	Message[1]->SetScale({ 4.0f,4.0f,1.0f });
	Message[1]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::TITLE);
		});

	Message[2] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_backTexture);
	Message[2]->SetPosition({ 5.0f,-3.0f,0 });
	Message[2]->SetScale({ 4.0f,4.0f,1.0f });
	Message[2]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::GAMEOVER);
		});

	// ボタン選択クラス作成
	selectControl = new ButtonSelect();
	selectControl->Regist(Message[0]);
	selectControl->Regist(Message[1]);
	selectControl->Regist(Message[2]);

	Player = new CWorldSelectPlayer(playerBuffer, playerTexture);
	Player->mTransform.pos = { 0,0,-1.0f };
	Player->mTransform.scale = { 4.0f,4.0f,1.0f };
	Player->isOnPlayer = false;

	isOnce = false;
	isNoMoving = false;
}

CGameOver::~CGameOver()
{
	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		CLASS_DELETE(Text[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		CLASS_DELETE(Message[i]);
	}

	CLASS_DELETE(Player);

	CLASS_DELETE(Bg);
}

void CGameOver::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	if (isNoMoving == false)
	{
		Bg->materialDiffuse.w += 0.01f;

		if (Bg->materialDiffuse.w > 0.5f)
		{
			Bg->SetAlpha(0.5f);
		}
		
		if (isOnce == false)
		{
			for (int i = 0; i < MAXNUM_TEXT; i++)
			{
				Text[i]->dotween->DoMoveY(3.0f, 1.0f);
			}

			Text[MAXNUM_MESSAGE]->dotween->OnComplete([&]()
				{
					isNoMoving = true;
				});

			isOnce = true;

		}
	}
	else {
		
		if (input->GetInputTrigger(InputType::DECIDE))
		{
			selectControl->PushButton();
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
	
	Bg->Update();

	Player->Update();
	
	for (int i = 0; i < MAXNUM_MESSAGE; i++)
	{
		Message[i]->Update();
	}

	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		Text[i]->Update();
	}
}

void CGameOver::LateUpdate()
{
}

void CGameOver::Draw()
{
	Bg->Draw();
	
	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		Text[i]->Draw();
	}

	if (isNoMoving == true)
	{
		for (int i = 0; i < MAXNUM_MESSAGE; i++)
		{
			Message[i]->Draw();
		}
		
		Player->Draw();

	}
}
