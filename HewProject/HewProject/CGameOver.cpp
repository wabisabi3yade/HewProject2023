#include "CGameOver.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"
#include "CWorldSelectPlayer.h"
#include "ButtonUI.h"

CGameOver::CGameOver()
{
	D3D_CreateSquare({ 3,1 }, &text_failedBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Sippai.png");

	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		Text[i] = new UI(text_failedBuffer, textTexture);
		Text[i]->MakeDotween();
	}

	D3D_CreateSquare({ 1,2 }, &textBoxBuffer);
	textBox1Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Blue.png");
	textBox2Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_White.png");
	textBox3Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Pink.png");
	textBoxTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_restartTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Restart.png");
	text_undoTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Undo.png");
	text_backTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Back.png");

	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_Wait.png");


	Text[0]->mTransform.pos = { -1.5f,6.0f,0 };
	Text[0]->mTransform.scale = { 2.0f,2.0f,1.0f };

	Text[1]->mTransform.pos = { 1.5f,6.0f,0 };
	Text[1]->mTransform.scale = { 2.0f,2.0f,1.0f };
	Text[1]->SetUV(1.0f/3.0f*1.0f,0);

	Text[2]->mTransform.pos = { 4.5f,6.0f,0 };
	Text[2]->mTransform.scale = { 2.0f,2.0f,1.0f };
	Text[2]->SetUV(1.0f / 3.0f * 2.0f, 0);

	Message[0] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_restartTexture);
	//Message[0]->MakeDotween();
	Message[0]->SetPosition({ -5.0f,-3.0f,0 });
	Message[0]->SetScale({ 4.0f,4.0f,1.0f });

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_undoTexture);
	//Message[1]->MakeDotween();
	Message[1]->SetPosition({ 0,-3.0f,0 });
	Message[1]->SetScale({ 4.0f,4.0f,1.0f });

	Message[2] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_backTexture);
	//Message[2]->MakeDotween();
	Message[2]->SetPosition({ 5.0f,-3.0f,0 });
	Message[2]->SetScale({ 4.0f,4.0f,1.0f });


	Player = new CWorldSelectPlayer(playerBuffer, playerTexture);
	Player->mTransform.pos = { 0,0,0 };
	Player->mTransform.scale = { 4.0f,4.0f,1.0f };
	Player->isOnPlayer = false;

	isOnce = false;
	isOnceBox = false;
	isNoMoving = false;
	isLate = false;
	nSelect = 0;
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
}

void CGameOver::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	if (isNoMoving == false)
	{
		if (isOnce == false)
		{
			for (int i = 0; i < MAXNUM_TEXT; i++)
			{
				Text[i]->dotween->DoMoveY(3.0f, 1.0f);
			}

			Text[0]->dotween->OnComplete([&]()
				{
					Text[0]->mTransform.rotation.z = 20.0f;
					isNoMoving = true;
				});

			isOnce = true;

		}
	}
	else {
		
		if (isLate == false)
		{
			if (input->GetMovement().x < 0)
			{
				isLate = true;
				nSelect--;
				if (nSelect < 0)
				{
					nSelect = 0;
				}

				if (isOnceBox == false)
				{
					isOnceBox = true;
					//Message[nSelect]->dotween->DoDelay(0.3f);
					/*Message[nSelect]->dotween->OnComplete([&]()
						{
							isLate = false;
							isOnceBox = false;
						});*/
				}
				

			}
			if (input->GetMovement().x > 0)
			{
				isLate = true;
				nSelect++;
				if (nSelect > 2)
				{
					nSelect = 2;
				}

				if (isOnceBox == false)
				{
					isOnceBox = true;
					/*Message[nSelect]->dotween->DoDelay(0.3f);
					Message[nSelect]->dotween->OnComplete([&]()
						{
							isLate = false;
							isOnceBox = false;
						});*/
				}
			}

			if (input->GetInputTrigger(InputType::DECIDE) && nSelect == 0)
			{
				CScene::SetScene(SCENE_NAME::SELECT);
			}

			if (input->GetInputTrigger(InputType::DECIDE) && nSelect == 1)
			{
				CScene::SetScene(SCENE_NAME::TITLE);
			}

			if (input->GetInputTrigger(InputType::DECIDE) && nSelect == 2)
			{
				CScene::SetScene(SCENE_NAME::GAMEOVER);
			}
		}
		
		if (nSelect == 0)
		{
			Message[0]->SetHighlight(true);
			Message[1]->SetHighlight(false);
			Message[2]->SetHighlight(false);
		}
		else if (nSelect == 1)
		{
			Message[0]->SetHighlight(false);
			Message[1]->SetHighlight(true);
			Message[2]->SetHighlight(false);
		}
		else if (nSelect == 2)
		{
			Message[0]->SetHighlight(false);
			Message[1]->SetHighlight(false);
			Message[2]->SetHighlight(true);
		}
	}
	
	
	Player->Update();
	
	for (int i = 0; i < 3; i++)
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
	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		Text[i]->Draw();
	}

	if (isNoMoving == true)
	{
		Message[0]->Draw();
		Message[1]->Draw();
		Message[2]->Draw();

		Player->Draw();

	}
}
